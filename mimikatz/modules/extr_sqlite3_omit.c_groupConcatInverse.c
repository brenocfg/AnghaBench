#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {scalar_t__ nChar; scalar_t__ mxAlloc; int /*<<< orphan*/ * zText; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void groupConcatInverse(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int n;
  StrAccum *pAccum;
  assert( argc==1 || argc==2 );
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
  pAccum = (StrAccum*)sqlite3_aggregate_context(context, sizeof(*pAccum));
  /* pAccum is always non-NULL since groupConcatStep() will have always
  ** run frist to initialize it */
  if( ALWAYS(pAccum) ){
    n = sqlite3_value_bytes(argv[0]);
    if( argc==2 ){
      n += sqlite3_value_bytes(argv[1]);
    }else{
      n++;
    }
    if( n>=(int)pAccum->nChar ){
      pAccum->nChar = 0;
    }else{
      pAccum->nChar -= n;
      memmove(pAccum->zText, &pAccum->zText[n], pAccum->nChar);
    }
    if( pAccum->nChar==0 ) pAccum->mxAlloc = 0;
  }
}