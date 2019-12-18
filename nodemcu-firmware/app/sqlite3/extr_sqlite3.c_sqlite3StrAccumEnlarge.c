#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_6__ {scalar_t__ nChar; scalar_t__ nAlloc; scalar_t__ accError; scalar_t__ mxAlloc; char* zText; char* zBase; int /*<<< orphan*/  printfFlags; scalar_t__ db; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_PRINTF_MALLOCED ; 
 scalar_t__ STRACCUM_NOMEM ; 
 scalar_t__ STRACCUM_TOOBIG ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isMalloced (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  setStrAccumError (TYPE_1__*,scalar_t__) ; 
 int sqlite3DbMallocSize (scalar_t__,char*) ; 
 char* sqlite3DbRealloc (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  sqlite3StrAccumReset (TYPE_1__*) ; 
 char* sqlite3_realloc64 (char*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int sqlite3StrAccumEnlarge(StrAccum *p, int N){
  char *zNew;
  assert( p->nChar+(i64)N >= p->nAlloc ); /* Only called if really needed */
  if( p->accError ){
    testcase(p->accError==STRACCUM_TOOBIG);
    testcase(p->accError==STRACCUM_NOMEM);
    return 0;
  }
  if( p->mxAlloc==0 ){
    N = p->nAlloc - p->nChar - 1;
    setStrAccumError(p, STRACCUM_TOOBIG);
    return N;
  }else{
    char *zOld = isMalloced(p) ? p->zText : 0;
    i64 szNew = p->nChar;
    assert( (p->zText==0 || p->zText==p->zBase)==!isMalloced(p) );
    szNew += N + 1;
    if( szNew+p->nChar<=p->mxAlloc ){
      /* Force exponential buffer size growth as long as it does not overflow,
      ** to avoid having to call this routine too often */
      szNew += p->nChar;
    }
    if( szNew > p->mxAlloc ){
      sqlite3StrAccumReset(p);
      setStrAccumError(p, STRACCUM_TOOBIG);
      return 0;
    }else{
      p->nAlloc = (int)szNew;
    }
    if( p->db ){
      zNew = sqlite3DbRealloc(p->db, zOld, p->nAlloc);
    }else{
      zNew = sqlite3_realloc64(zOld, p->nAlloc);
    }
    if( zNew ){
      assert( p->zText!=0 || p->nChar==0 );
      if( !isMalloced(p) && p->nChar>0 ) memcpy(zNew, p->zText, p->nChar);
      p->zText = zNew;
      p->nAlloc = sqlite3DbMallocSize(p->db, zNew);
      p->printfFlags |= SQLITE_PRINTF_MALLOCED;
    }else{
      sqlite3StrAccumReset(p);
      setStrAccumError(p, STRACCUM_NOMEM);
      return 0;
    }
  }
  return N;
}