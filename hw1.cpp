#include <string>
#include <iostream>
#include <fstream>
using namespace std;

static int NumAllocations = 0; 



class MyString
{
  char * buf;

public:

  MyString( const char *s) {
    int len;
    int i;
    for (i = 0; ; i++) {
      if (s[i] == '\0') {
        break;
      }
    }
    len = i + 1;
    buf = new char[len];
    for (int i = 0; i < len; i++) {
      buf[i] = s[i];
    }
  }

// copy constructor for a MyString, must make a deep copy of s for this
  MyString( const MyString & s ) {
    int len = s.length();
    buf = new char[len];
    for (i = 0; i < len; i++) {
      buf[i] = s.buf[i];	    
    }
  }


// assigns this MyString from MyString s, MUST DO DEEP ASSIGNMENT
// remember, both this and s have been previously constructed
// so they each have storage pointed to by buf
  MyString operator = ( const MyString & s ) {
    int len = s.length();
    buf = new char[len];
    for (int i = 0; i < len; i++) {
      buf[i] = s.buf[i];
    }
    return *this;
  }



// return a reference to the char at position index, 0 is the first element and so on
// index must be in bounds (see method above)
  char & operator [] ( const int index ) {
    return buf[index];
  }


  int length() const {
    for (int i = 0; ; i++) {
      if (buf[i] == '\0') {
        return i;
      }
    }
    return -1;
  }



// returns the index of the first occurance of c in this MyString
// indices range from 0 to length()-1
// returns -1 if the character c is not in this MyString
  int indexOf( char c ) const {
    int len = length();
    for (int i = 0; i < len; i++) {
      if (buf[i] == c) {
        return i;
      }
    }
      return -1;
  } 
                
                
                
// True if the two MyStrings contain the same chars in same position
// e.g, "abc"=="abc" returns true
  bool operator == ( const MyString & s ) const {
  int len = length();
  for (int i = 0; i < len; i++) {
    if (buf[i] != s.buf[i]) {
      return 0;
    }
  }
  return 1;
  }




// concatenates this and s to make a new MyString
// e.g., "abc"+"def" returns "abcdef"
  MyString operator + ( const MyString & s ) const {
  MyString newString("");
  int len0 = length();
  int len = len0 + s.length();
  newString.buf = new char[len];
  for (int i = 0; i < len; i++) {
    if (i < len0) {
      newString.buf[i] = buf[i];
    }
    else {
      newString.buf[i] = s.buf[i-len0];
    }
  }
  return newString;
  }



// concatenates s onto end of this
// e.g., s = "abc"; s+="def" now s is "abcdef"
  MyString operator += ( const MyString & s ) {
    int len0 = length();
    int len = len0 + s.length();
    char * buf2 = new char[len];
    for (int i = 0; i < len; i++) {
      if (i < len0) {
        buf2[i] = buf[i];
      }
      else {
        buf2[i] = s.buf[i-len0];
      }
    }
    delete buf;
    buf = buf2;
    return *this;
  }



// returns another MyString that is the reverse of this MyString
// e.g., s = "abc"; s.reverse() returns "cba"

/*MyString reverse()
{
MyString
int len = length();
char tmp;
for (i = 0; i < len-1-i; i++) {
  tmp = buf[i];
  buf[i] = buf[len - 1 - i];
  buf[len - 1 - i] = tmp;
}
return *this;
}
*/

  MyString reverse() {
    MyString newString("");
    int len = length();
    newString.buf = new char[length()];
    for (int i = 0; i < len; i++) {
      newString.buf[i] = buf[len - 1 - i];
    }
    return newString;
  }


// prints out this MyString to the ostream out
  void print( ostream & out ) const {
    out << buf << endl;
  }


// reads a word from the istream in and this MyString
// becomes the same as the characters in that word
  void read( istream & in ) {
    string s;
    in >> s;
    buf = s.c_str();
  }



// destruct a MyString, must free up each node in the head list
  ~MyString() {
    delete buf;
  }

// utility method to handle errors, note throws an exception to prevent
// access to undefined values. Always call this method when you detect a fatal error from
// any of your methods.
  void error(const char *s) {
    cerr << "Error: " << s << endl;
    throw 0;
  }


};







// these two I/O methods are complete as long as you define print and read methods correctly
inline ostream & operator << ( ostream & out, const MyString & str )
{
str.print(out);
return out;
}
inline istream & operator >> ( istream & in, MyString & str )
{
str.read(in);
return in;
}
// TBD: Write all these testing functions and add more of your own
// follow my example and write a function to test each method.
// Name each of these functions so they clearly indicate what they are testing
MyString copyConstructorTest(MyString l)
{
return l;
}
void testReverse()
{
ifstream in("input.txt");
MyString l;
while ( in >> l )
cout << copyConstructorTest(l)
<< " " << l.length() << " "
<< l.reverse() << endl;
}
// write more test functions here
// ...
int main()
{
// This try/catch will catch any exception thrown by MyString::error()
// while calling test functions.
try {
testReverse();
// put more test function calls here written just above
}
catch (int i) {
cout << "Got an exception: " << i << endl;
}
cerr << "Net memory allocated at program end: " << NumAllocations << endl;
cerr << "(should be zero! positive = memory leak, negative = duplicate delete)\n";
return 0;
}



