#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int errCode; scalar_t__ eState; scalar_t__ dbSize; scalar_t__ doNotSyncSpill; scalar_t__ doNotSpill; } ;
struct TYPE_15__ {int flags; scalar_t__ pgno; scalar_t__ pDirty; TYPE_2__* pPager; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  PAGERID (TYPE_2__*) ; 
 int /*<<< orphan*/  PAGERTRACE (char*) ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 int PGHDR_DIRTY ; 
 int PGHDR_NEED_SYNC ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pagerUseWal (TYPE_2__*) ; 
 int pagerWalFrames (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pager_error (TYPE_2__*,int) ; 
 int pager_write_pagelist (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3PcacheMakeClean (TYPE_1__*) ; 
 scalar_t__ subjRequiresPage (TYPE_1__*) ; 
 int subjournalPage (TYPE_1__*) ; 
 int syncJournal (TYPE_2__*,int) ; 

__attribute__((used)) static int pagerStress(void *p, PgHdr *pPg){
  Pager *pPager = (Pager *)p;
  int rc = SQLITE_OK;

  assert( pPg->pPager==pPager );
  assert( pPg->flags&PGHDR_DIRTY );

  /* The doNotSyncSpill flag is set during times when doing a sync of
  ** journal (and adding a new header) is not allowed.  This occurs
  ** during calls to sqlite3PagerWrite() while trying to journal multiple
  ** pages belonging to the same sector.
  **
  ** The doNotSpill flag inhibits all cache spilling regardless of whether
  ** or not a sync is required.  This is set during a rollback.
  **
  ** Spilling is also prohibited when in an error state since that could
  ** lead to database corruption.   In the current implementaton it 
  ** is impossible for sqlite3PcacheFetch() to be called with createFlag==1
  ** while in the error state, hence it is impossible for this routine to
  ** be called in the error state.  Nevertheless, we include a NEVER()
  ** test for the error state as a safeguard against future changes.
  */
  if( NEVER(pPager->errCode) ) return SQLITE_OK;
  if( pPager->doNotSpill ) return SQLITE_OK;
  if( pPager->doNotSyncSpill && (pPg->flags & PGHDR_NEED_SYNC)!=0 ){
    return SQLITE_OK;
  }

  pPg->pDirty = 0;
  if( pagerUseWal(pPager) ){
    /* Write a single frame for this page to the log. */
    if( subjRequiresPage(pPg) ){ 
      rc = subjournalPage(pPg); 
    }
    if( rc==SQLITE_OK ){
      rc = pagerWalFrames(pPager, pPg, 0, 0);
    }
  }else{
  
    /* Sync the journal file if required. */
    if( pPg->flags&PGHDR_NEED_SYNC 
     || pPager->eState==PAGER_WRITER_CACHEMOD
    ){
      rc = syncJournal(pPager, 1);
    }
  
    /* If the page number of this page is larger than the current size of
    ** the database image, it may need to be written to the sub-journal.
    ** This is because the call to pager_write_pagelist() below will not
    ** actually write data to the file in this case.
    **
    ** Consider the following sequence of events:
    **
    **   BEGIN;
    **     <journal page X>
    **     <modify page X>
    **     SAVEPOINT sp;
    **       <shrink database file to Y pages>
    **       pagerStress(page X)
    **     ROLLBACK TO sp;
    **
    ** If (X>Y), then when pagerStress is called page X will not be written
    ** out to the database file, but will be dropped from the cache. Then,
    ** following the "ROLLBACK TO sp" statement, reading page X will read
    ** data from the database file. This will be the copy of page X as it
    ** was when the transaction started, not as it was when "SAVEPOINT sp"
    ** was executed.
    **
    ** The solution is to write the current data for page X into the 
    ** sub-journal file now (if it is not already there), so that it will
    ** be restored to its current value when the "ROLLBACK TO sp" is 
    ** executed.
    */
    if( NEVER(
        rc==SQLITE_OK && pPg->pgno>pPager->dbSize && subjRequiresPage(pPg)
    ) ){
      rc = subjournalPage(pPg);
    }
  
    /* Write the contents of the page out to the database file. */
    if( rc==SQLITE_OK ){
      assert( (pPg->flags&PGHDR_NEED_SYNC)==0 );
      rc = pager_write_pagelist(pPager, pPg);
    }
  }

  /* Mark the page as clean. */
  if( rc==SQLITE_OK ){
    PAGERTRACE(("STRESS %d page %d\n", PAGERID(pPager), pPg->pgno));
    sqlite3PcacheMakeClean(pPg);
  }

  return pager_error(pPager, rc); 
}