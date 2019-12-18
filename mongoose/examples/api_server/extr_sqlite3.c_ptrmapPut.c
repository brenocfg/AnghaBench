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
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int autoVacuum; scalar_t__ usableSize; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ Pgno ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  PENDING_BYTE_PAGE (TYPE_1__*) ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PTRMAP_PAGENO (TYPE_1__*,scalar_t__) ; 
 int PTRMAP_PTROFFSET (scalar_t__,scalar_t__) ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get4byte (scalar_t__*) ; 
 int /*<<< orphan*/  put4byte (scalar_t__*,scalar_t__) ; 
 int sqlite3PagerGet (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3PagerGetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3PagerUnref (int /*<<< orphan*/ *) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ptrmapPut(BtShared *pBt, Pgno key, u8 eType, Pgno parent, int *pRC){
  DbPage *pDbPage;  /* The pointer map page */
  u8 *pPtrmap;      /* The pointer map data */
  Pgno iPtrmap;     /* The pointer map page number */
  int offset;       /* Offset in pointer map page */
  int rc;           /* Return code from subfunctions */

  if( *pRC ) return;

  assert( sqlite3_mutex_held(pBt->mutex) );
  /* The master-journal page number must never be used as a pointer map page */
  assert( 0==PTRMAP_ISPAGE(pBt, PENDING_BYTE_PAGE(pBt)) );

  assert( pBt->autoVacuum );
  if( key==0 ){
    *pRC = SQLITE_CORRUPT_BKPT;
    return;
  }
  iPtrmap = PTRMAP_PAGENO(pBt, key);
  rc = sqlite3PagerGet(pBt->pPager, iPtrmap, &pDbPage);
  if( rc!=SQLITE_OK ){
    *pRC = rc;
    return;
  }
  offset = PTRMAP_PTROFFSET(iPtrmap, key);
  if( offset<0 ){
    *pRC = SQLITE_CORRUPT_BKPT;
    goto ptrmap_exit;
  }
  assert( offset <= (int)pBt->usableSize-5 );
  pPtrmap = (u8 *)sqlite3PagerGetData(pDbPage);

  if( eType!=pPtrmap[offset] || get4byte(&pPtrmap[offset+1])!=parent ){
    TRACE(("PTRMAP_UPDATE: %d->(%d,%d)\n", key, eType, parent));
    *pRC= rc = sqlite3PagerWrite(pDbPage);
    if( rc==SQLITE_OK ){
      pPtrmap[offset] = eType;
      put4byte(&pPtrmap[offset+1], parent);
    }
  }

ptrmap_exit:
  sqlite3PagerUnref(pDbPage);
}