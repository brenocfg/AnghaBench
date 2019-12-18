#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;
struct TYPE_2__ {int* aLimit; } ;

/* Variables and functions */
 int SQLITE_BLOB ; 
 size_t SQLITE_LIMIT_LENGTH ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_SKIP_UTF8 (unsigned char const*) ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_blob64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text64 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void substrFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *z;
  const unsigned char *z2;
  int len;
  int p0type;
  i64 p1, p2;
  int negP2 = 0;

  assert( argc==3 || argc==2 );
  if( sqlite3_value_type(argv[1])==SQLITE_NULL
   || (argc==3 && sqlite3_value_type(argv[2])==SQLITE_NULL)
  ){
    return;
  }
  p0type = sqlite3_value_type(argv[0]);
  p1 = sqlite3_value_int(argv[1]);
  if( p0type==SQLITE_BLOB ){
    len = sqlite3_value_bytes(argv[0]);
    z = sqlite3_value_blob(argv[0]);
    if( z==0 ) return;
    assert( len==sqlite3_value_bytes(argv[0]) );
  }else{
    z = sqlite3_value_text(argv[0]);
    if( z==0 ) return;
    len = 0;
    if( p1<0 ){
      for(z2=z; *z2; len++){
        SQLITE_SKIP_UTF8(z2);
      }
    }
  }
#ifdef SQLITE_SUBSTR_COMPATIBILITY
  /* If SUBSTR_COMPATIBILITY is defined then substr(X,0,N) work the same as
  ** as substr(X,1,N) - it returns the first N characters of X.  This
  ** is essentially a back-out of the bug-fix in check-in [5fc125d362df4b8]
  ** from 2009-02-02 for compatibility of applications that exploited the
  ** old buggy behavior. */
  if( p1==0 ) p1 = 1; /* <rdar://problem/6778339> */
#endif
  if( argc==3 ){
    p2 = sqlite3_value_int(argv[2]);
    if( p2<0 ){
      p2 = -p2;
      negP2 = 1;
    }
  }else{
    p2 = sqlite3_context_db_handle(context)->aLimit[SQLITE_LIMIT_LENGTH];
  }
  if( p1<0 ){
    p1 += len;
    if( p1<0 ){
      p2 += p1;
      if( p2<0 ) p2 = 0;
      p1 = 0;
    }
  }else if( p1>0 ){
    p1--;
  }else if( p2>0 ){
    p2--;
  }
  if( negP2 ){
    p1 -= p2;
    if( p1<0 ){
      p2 += p1;
      p1 = 0;
    }
  }
  assert( p1>=0 && p2>=0 );
  if( p0type!=SQLITE_BLOB ){
    while( *z && p1 ){
      SQLITE_SKIP_UTF8(z);
      p1--;
    }
    for(z2=z; *z2 && p2; p2--){
      SQLITE_SKIP_UTF8(z2);
    }
    sqlite3_result_text64(context, (char*)z, z2-z, SQLITE_TRANSIENT,
                          SQLITE_UTF8);
  }else{
    if( p1+p2>len ){
      p2 = len-p1;
      if( p2<0 ) p2 = 0;
    }
    sqlite3_result_blob64(context, (char*)&z[p1], (u64)p2, SQLITE_TRANSIENT);
  }
}