#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ usableSize; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int PTRMAP_PAGENO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PTRMAP_PTROFFSET (int,int /*<<< orphan*/ ) ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get4byte (int*) ; 
 int sqlite3PagerGet (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PagerGetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3PagerUnref (int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptrmapGet(BtShared *pBt, Pgno key, u8 *pEType, Pgno *pPgno){
  DbPage *pDbPage;   /* The pointer map page */
  int iPtrmap;       /* Pointer map page index */
  u8 *pPtrmap;       /* Pointer map page data */
  int offset;        /* Offset of entry in pointer map */
  int rc;

  assert( sqlite3_mutex_held(pBt->mutex) );

  iPtrmap = PTRMAP_PAGENO(pBt, key);
  rc = sqlite3PagerGet(pBt->pPager, iPtrmap, &pDbPage, 0);
  if( rc!=0 ){
    return rc;
  }
  pPtrmap = (u8 *)sqlite3PagerGetData(pDbPage);

  offset = PTRMAP_PTROFFSET(iPtrmap, key);
  if( offset<0 ){
    sqlite3PagerUnref(pDbPage);
    return SQLITE_CORRUPT_BKPT;
  }
  assert( offset <= (int)pBt->usableSize-5 );
  assert( pEType!=0 );
  *pEType = pPtrmap[offset];
  if( pPgno ) *pPgno = get4byte(&pPtrmap[offset+1]);

  sqlite3PagerUnref(pDbPage);
  if( *pEType<1 || *pEType>5 ) return SQLITE_CORRUPT_BKPT;
  return SQLITE_OK;
}