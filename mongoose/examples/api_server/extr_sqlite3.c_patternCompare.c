#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct compareInfo {int matchOne; int matchAll; int matchSet; int noCase; } ;

/* Variables and functions */
 int /*<<< orphan*/  GlogUpperToLower (int) ; 
 int /*<<< orphan*/  SQLITE_SKIP_UTF8 (int const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Utf8Read (int const**) ; 

__attribute__((used)) static int patternCompare(
  const u8 *zPattern,              /* The glob pattern */
  const u8 *zString,               /* The string to compare against the glob */
  const struct compareInfo *pInfo, /* Information about how to do the compare */
  u32 esc                          /* The escape character */
){
  u32 c, c2;
  int invert;
  int seen;
  u8 matchOne = pInfo->matchOne;
  u8 matchAll = pInfo->matchAll;
  u8 matchSet = pInfo->matchSet;
  u8 noCase = pInfo->noCase; 
  int prevEscape = 0;     /* True if the previous character was 'escape' */

  while( (c = sqlite3Utf8Read(&zPattern))!=0 ){
    if( c==matchAll && !prevEscape ){
      while( (c=sqlite3Utf8Read(&zPattern)) == matchAll
               || c == matchOne ){
        if( c==matchOne && sqlite3Utf8Read(&zString)==0 ){
          return 0;
        }
      }
      if( c==0 ){
        return 1;
      }else if( c==esc ){
        c = sqlite3Utf8Read(&zPattern);
        if( c==0 ){
          return 0;
        }
      }else if( c==matchSet ){
        assert( esc==0 );         /* This is GLOB, not LIKE */
        assert( matchSet<0x80 );  /* '[' is a single-byte character */
        while( *zString && patternCompare(&zPattern[-1],zString,pInfo,esc)==0 ){
          SQLITE_SKIP_UTF8(zString);
        }
        return *zString!=0;
      }
      while( (c2 = sqlite3Utf8Read(&zString))!=0 ){
        if( noCase ){
          GlogUpperToLower(c2);
          GlogUpperToLower(c);
          while( c2 != 0 && c2 != c ){
            c2 = sqlite3Utf8Read(&zString);
            GlogUpperToLower(c2);
          }
        }else{
          while( c2 != 0 && c2 != c ){
            c2 = sqlite3Utf8Read(&zString);
          }
        }
        if( c2==0 ) return 0;
        if( patternCompare(zPattern,zString,pInfo,esc) ) return 1;
      }
      return 0;
    }else if( c==matchOne && !prevEscape ){
      if( sqlite3Utf8Read(&zString)==0 ){
        return 0;
      }
    }else if( c==matchSet ){
      u32 prior_c = 0;
      assert( esc==0 );    /* This only occurs for GLOB, not LIKE */
      seen = 0;
      invert = 0;
      c = sqlite3Utf8Read(&zString);
      if( c==0 ) return 0;
      c2 = sqlite3Utf8Read(&zPattern);
      if( c2=='^' ){
        invert = 1;
        c2 = sqlite3Utf8Read(&zPattern);
      }
      if( c2==']' ){
        if( c==']' ) seen = 1;
        c2 = sqlite3Utf8Read(&zPattern);
      }
      while( c2 && c2!=']' ){
        if( c2=='-' && zPattern[0]!=']' && zPattern[0]!=0 && prior_c>0 ){
          c2 = sqlite3Utf8Read(&zPattern);
          if( c>=prior_c && c<=c2 ) seen = 1;
          prior_c = 0;
        }else{
          if( c==c2 ){
            seen = 1;
          }
          prior_c = c2;
        }
        c2 = sqlite3Utf8Read(&zPattern);
      }
      if( c2==0 || (seen ^ invert)==0 ){
        return 0;
      }
    }else if( esc==c && !prevEscape ){
      prevEscape = 1;
    }else{
      c2 = sqlite3Utf8Read(&zString);
      if( noCase ){
        GlogUpperToLower(c);
        GlogUpperToLower(c2);
      }
      if( c!=c2 ){
        return 0;
      }
      prevEscape = 0;
    }
  }
  return *zString==0;
}