#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int doNotSpill; scalar_t__ eState; int /*<<< orphan*/  errCode; } ;
struct TYPE_14__ {int flags; int /*<<< orphan*/  pgno; scalar_t__ pDirty; TYPE_2__* pPager; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ NEVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGERID (TYPE_2__*) ; 
 int /*<<< orphan*/  PAGERTRACE (char*) ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 int PGHDR_DIRTY ; 
 int PGHDR_NEED_SYNC ; 
 int SPILLFLAG_NOSYNC ; 
 int SPILLFLAG_OFF ; 
 int SPILLFLAG_ROLLBACK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pagerUseWal (TYPE_2__*) ; 
 int pagerWalFrames (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pager_error (TYPE_2__*,int) ; 
 int pager_write_pagelist (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3PcacheMakeClean (TYPE_1__*) ; 
 int subjournalPageIfRequired (TYPE_1__*) ; 
 int syncJournal (TYPE_2__*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int pagerStress(void *p, PgHdr *pPg){
  Pager *pPager = (Pager *)p;
  int rc = SQLITE_OK;

  assert( pPg->pPager==pPager );
  assert( pPg->flags&PGHDR_DIRTY );

  /* The doNotSpill NOSYNC bit is set during times when doing a sync of
  ** journal (and adding a new header) is not allowed.  This occurs
  ** during calls to sqlite3PagerWrite() while trying to journal multiple
  ** pages belonging to the same sector.
  **
  ** The doNotSpill ROLLBACK and OFF bits inhibits all cache spilling
  ** regardless of whether or not a sync is required.  This is set during
  ** a rollback or by user request, respectively.
  **
  ** Spilling is also prohibited when in an error state since that could
  ** lead to database corruption.   In the current implementation it
  ** is impossible for sqlite3PcacheFetch() to be called with createFlag==3
  ** while in the error state, hence it is impossible for this routine to
  ** be called in the error state.  Nevertheless, we include a NEVER()
  ** test for the error state as a safeguard against future changes.
  */
  if( NEVER(pPager->errCode) ) return SQLITE_OK;
  testcase( pPager->doNotSpill & SPILLFLAG_ROLLBACK );
  testcase( pPager->doNotSpill & SPILLFLAG_OFF );
  testcase( pPager->doNotSpill & SPILLFLAG_NOSYNC );
  if( pPager->doNotSpill
   && ((pPager->doNotSpill & (SPILLFLAG_ROLLBACK|SPILLFLAG_OFF))!=0
      || (pPg->flags & PGHDR_NEED_SYNC)!=0)
  ){
    return SQLITE_OK;
  }

  pPg->pDirty = 0;
  if( pagerUseWal(pPager) ){
    /* Write a single frame for this page to the log. */
    rc = subjournalPageIfRequired(pPg);
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