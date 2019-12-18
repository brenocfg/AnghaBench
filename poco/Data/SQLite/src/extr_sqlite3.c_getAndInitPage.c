#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int curPagerFlags; size_t iPage; scalar_t__ curIntKey; TYPE_1__** apPage; TYPE_1__* pPage; } ;
struct TYPE_12__ {int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
struct TYPE_11__ {scalar_t__ isInit; scalar_t__ aData; int nCell; scalar_t__ intKey; int /*<<< orphan*/  pgno; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  TYPE_2__ BtShared ;
typedef  TYPE_3__ BtCursor ;

/* Variables and functions */
 int SQLITE_CORRUPT ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_CORRUPT_PGNO (int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeInitPage (TYPE_1__*) ; 
 int /*<<< orphan*/  btreePageFromDbPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  btreePagecount (TYPE_2__*) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 int sqlite3PagerGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ sqlite3PagerGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3PagerGetExtra (int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int getAndInitPage(
  BtShared *pBt,                  /* The database file */
  Pgno pgno,                      /* Number of the page to get */
  MemPage **ppPage,               /* Write the page pointer here */
  BtCursor *pCur,                 /* Cursor to receive the page, or NULL */
  int bReadOnly                   /* True for a read-only page */
){
  int rc;
  DbPage *pDbPage;
  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( pCur==0 || ppPage==&pCur->pPage );
  assert( pCur==0 || bReadOnly==pCur->curPagerFlags );
  assert( pCur==0 || pCur->iPage>0 );

  if( pgno>btreePagecount(pBt) ){
    rc = SQLITE_CORRUPT_BKPT;
    goto getAndInitPage_error1;
  }
  rc = sqlite3PagerGet(pBt->pPager, pgno, (DbPage**)&pDbPage, bReadOnly);
  if( rc ){
    goto getAndInitPage_error1;
  }
  *ppPage = (MemPage*)sqlite3PagerGetExtra(pDbPage);
  if( (*ppPage)->isInit==0 ){
    btreePageFromDbPage(pDbPage, pgno, pBt);
    rc = btreeInitPage(*ppPage);
    if( rc!=SQLITE_OK ){
      goto getAndInitPage_error2;
    }
  }
  assert( (*ppPage)->pgno==pgno );
  assert( (*ppPage)->aData==sqlite3PagerGetData(pDbPage) );

  /* If obtaining a child page for a cursor, we must verify that the page is
  ** compatible with the root page. */
  if( pCur && ((*ppPage)->nCell<1 || (*ppPage)->intKey!=pCur->curIntKey) ){
    rc = SQLITE_CORRUPT_PGNO(pgno);
    goto getAndInitPage_error2;
  }
  return SQLITE_OK;

getAndInitPage_error2:
  releasePage(*ppPage);
getAndInitPage_error1:
  if( pCur ){
    pCur->iPage--;
    pCur->pPage = pCur->apPage[pCur->iPage];
  }
  testcase( pgno==0 );
  assert( pgno!=0 || rc==SQLITE_CORRUPT );
  return rc;
}