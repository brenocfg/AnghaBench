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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* contextMalloc (int /*<<< orphan*/ *,int) ; 
 void** hexdigits ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 unsigned char const* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hexFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int i, n;
  const unsigned char *pBlob;
  char *zHex, *z;
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  pBlob = sqlite3_value_blob(argv[0]);
  n = sqlite3_value_bytes(argv[0]);
  assert( pBlob==sqlite3_value_blob(argv[0]) );  /* No encoding change */
  z = zHex = contextMalloc(context, ((i64)n)*2 + 1);
  if( zHex ){
    for(i=0; i<n; i++, pBlob++){
      unsigned char c = *pBlob;
      *(z++) = hexdigits[(c>>4)&0xf];
      *(z++) = hexdigits[c&0xf];
    }
    *z = 0;
    sqlite3_result_text(context, zHex, n*2, sqlite3_free);
  }
}