#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pPCache; int /*<<< orphan*/  pWal; int /*<<< orphan*/  dbOrigSize; int /*<<< orphan*/  dbSize; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgno; struct TYPE_5__* pDirty; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int SQLITE_OK ; 
 int pagerUndoCallback (void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3PcacheDirtyList (int /*<<< orphan*/ ) ; 
 int sqlite3WalUndo (int /*<<< orphan*/ ,int (*) (void*,int /*<<< orphan*/ ),void*) ; 

__attribute__((used)) static int pagerRollbackWal(Pager *pPager){
  int rc;                         /* Return Code */
  PgHdr *pList;                   /* List of dirty pages to revert */

  /* For all pages in the cache that are currently dirty or have already
  ** been written (but not committed) to the log file, do one of the 
  ** following:
  **
  **   + Discard the cached page (if refcount==0), or
  **   + Reload page content from the database (if refcount>0).
  */
  pPager->dbSize = pPager->dbOrigSize;
  rc = sqlite3WalUndo(pPager->pWal, pagerUndoCallback, (void *)pPager);
  pList = sqlite3PcacheDirtyList(pPager->pPCache);
  while( pList && rc==SQLITE_OK ){
    PgHdr *pNext = pList->pDirty;
    rc = pagerUndoCallback((void *)pPager, pList->pgno);
    pList = pNext;
  }

  return rc;
}