#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_16__ {int usableSize; int /*<<< orphan*/  mutex; } ;
struct TYPE_15__ {int iOverflow; int nPayload; int nLocal; } ;
struct TYPE_14__ {unsigned char* aData; int maskPage; int /*<<< orphan*/  pDbPage; TYPE_3__* pBt; } ;
typedef  int Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellInfo ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* btreePageLookup (TYPE_3__*,int) ; 
 int btreePagecount (TYPE_3__*) ; 
 int /*<<< orphan*/  btreeParseCellPtr (TYPE_1__*,unsigned char*,TYPE_2__*) ; 
 int freePage2 (TYPE_3__*,TYPE_1__*,int) ; 
 int get4byte (unsigned char*) ; 
 int getOverflowPage (TYPE_3__*,int,TYPE_1__**,int*) ; 
 int sqlite3PagerPageRefcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerUnref (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clearCell(MemPage *pPage, unsigned char *pCell){
  BtShared *pBt = pPage->pBt;
  CellInfo info;
  Pgno ovflPgno;
  int rc;
  int nOvfl;
  u32 ovflPageSize;

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  btreeParseCellPtr(pPage, pCell, &info);
  if( info.iOverflow==0 ){
    return SQLITE_OK;  /* No overflow pages. Return without doing anything */
  }
  if( pCell+info.iOverflow+3 > pPage->aData+pPage->maskPage ){
    return SQLITE_CORRUPT_BKPT;  /* Cell extends past end of page */
  }
  ovflPgno = get4byte(&pCell[info.iOverflow]);
  assert( pBt->usableSize > 4 );
  ovflPageSize = pBt->usableSize - 4;
  nOvfl = (info.nPayload - info.nLocal + ovflPageSize - 1)/ovflPageSize;
  assert( ovflPgno==0 || nOvfl>0 );
  while( nOvfl-- ){
    Pgno iNext = 0;
    MemPage *pOvfl = 0;
    if( ovflPgno<2 || ovflPgno>btreePagecount(pBt) ){
      /* 0 is not a legal page number and page 1 cannot be an 
      ** overflow page. Therefore if ovflPgno<2 or past the end of the 
      ** file the database must be corrupt. */
      return SQLITE_CORRUPT_BKPT;
    }
    if( nOvfl ){
      rc = getOverflowPage(pBt, ovflPgno, &pOvfl, &iNext);
      if( rc ) return rc;
    }

    if( ( pOvfl || ((pOvfl = btreePageLookup(pBt, ovflPgno))!=0) )
     && sqlite3PagerPageRefcount(pOvfl->pDbPage)!=1
    ){
      /* There is no reason any cursor should have an outstanding reference 
      ** to an overflow page belonging to a cell that is being deleted/updated.
      ** So if there exists more than one reference to this page, then it 
      ** must not really be an overflow page and the database must be corrupt. 
      ** It is helpful to detect this before calling freePage2(), as 
      ** freePage2() may zero the page contents if secure-delete mode is
      ** enabled. If this 'overflow' page happens to be a page that the
      ** caller is iterating through or using in some other way, this
      ** can be problematic.
      */
      rc = SQLITE_CORRUPT_BKPT;
    }else{
      rc = freePage2(pBt, pOvfl, ovflPgno);
    }

    if( pOvfl ){
      sqlite3PagerUnref(pOvfl->pDbPage);
    }
    if( rc ) return rc;
    ovflPgno = iNext;
  }
  return SQLITE_OK;
}