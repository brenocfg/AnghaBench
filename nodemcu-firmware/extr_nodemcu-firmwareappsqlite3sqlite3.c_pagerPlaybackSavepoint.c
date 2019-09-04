#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ i64 ;
struct TYPE_12__ {scalar_t__ eState; scalar_t__ journalOff; scalar_t__ journalHdr; int pageSize; scalar_t__ nSubRec; int /*<<< orphan*/  pWal; int /*<<< orphan*/  tempFile; int /*<<< orphan*/  changeCountDone; int /*<<< orphan*/  dbOrigSize; int /*<<< orphan*/  dbSize; } ;
struct TYPE_11__ {scalar_t__ iHdrOffset; scalar_t__ iOffset; scalar_t__ iSubRec; int /*<<< orphan*/  aWalData; int /*<<< orphan*/  nOrig; } ;
typedef  TYPE_1__ PagerSavepoint ;
typedef  TYPE_2__ Pager ;
typedef  int /*<<< orphan*/  Bitvec ;

/* Variables and functions */
 scalar_t__ JOURNAL_HDR_SZ (TYPE_2__*) ; 
 scalar_t__ JOURNAL_PG_SZ (TYPE_2__*) ; 
 scalar_t__ PAGER_ERROR ; 
 scalar_t__ PAGER_WRITER_LOCKED ; 
 int SQLITE_DONE ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerRollbackWal (TYPE_2__*) ; 
 scalar_t__ pagerUseWal (TYPE_2__*) ; 
 int pager_playback_one_page (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *,int,int) ; 
 int readJournalHdr (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * sqlite3BitvecCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BitvecDestroy (int /*<<< orphan*/ *) ; 
 int sqlite3WalSavepointUndo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pagerPlaybackSavepoint(Pager *pPager, PagerSavepoint *pSavepoint){
  i64 szJ;                 /* Effective size of the main journal */
  i64 iHdrOff;             /* End of first segment of main-journal records */
  int rc = SQLITE_OK;      /* Return code */
  Bitvec *pDone = 0;       /* Bitvec to ensure pages played back only once */

  assert( pPager->eState!=PAGER_ERROR );
  assert( pPager->eState>=PAGER_WRITER_LOCKED );

  /* Allocate a bitvec to use to store the set of pages rolled back */
  if( pSavepoint ){
    pDone = sqlite3BitvecCreate(pSavepoint->nOrig);
    if( !pDone ){
      return SQLITE_NOMEM_BKPT;
    }
  }

  /* Set the database size back to the value it was before the savepoint
  ** being reverted was opened.
  */
  pPager->dbSize = pSavepoint ? pSavepoint->nOrig : pPager->dbOrigSize;
  pPager->changeCountDone = pPager->tempFile;

  if( !pSavepoint && pagerUseWal(pPager) ){
    return pagerRollbackWal(pPager);
  }

  /* Use pPager->journalOff as the effective size of the main rollback
  ** journal.  The actual file might be larger than this in
  ** PAGER_JOURNALMODE_TRUNCATE or PAGER_JOURNALMODE_PERSIST.  But anything
  ** past pPager->journalOff is off-limits to us.
  */
  szJ = pPager->journalOff;
  assert( pagerUseWal(pPager)==0 || szJ==0 );

  /* Begin by rolling back records from the main journal starting at
  ** PagerSavepoint.iOffset and continuing to the next journal header.
  ** There might be records in the main journal that have a page number
  ** greater than the current database size (pPager->dbSize) but those
  ** will be skipped automatically.  Pages are added to pDone as they
  ** are played back.
  */
  if( pSavepoint && !pagerUseWal(pPager) ){
    iHdrOff = pSavepoint->iHdrOffset ? pSavepoint->iHdrOffset : szJ;
    pPager->journalOff = pSavepoint->iOffset;
    while( rc==SQLITE_OK && pPager->journalOff<iHdrOff ){
      rc = pager_playback_one_page(pPager, &pPager->journalOff, pDone, 1, 1);
    }
    assert( rc!=SQLITE_DONE );
  }else{
    pPager->journalOff = 0;
  }

  /* Continue rolling back records out of the main journal starting at
  ** the first journal header seen and continuing until the effective end
  ** of the main journal file.  Continue to skip out-of-range pages and
  ** continue adding pages rolled back to pDone.
  */
  while( rc==SQLITE_OK && pPager->journalOff<szJ ){
    u32 ii;            /* Loop counter */
    u32 nJRec = 0;     /* Number of Journal Records */
    u32 dummy;
    rc = readJournalHdr(pPager, 0, szJ, &nJRec, &dummy);
    assert( rc!=SQLITE_DONE );

    /*
    ** The "pPager->journalHdr+JOURNAL_HDR_SZ(pPager)==pPager->journalOff"
    ** test is related to ticket #2565.  See the discussion in the
    ** pager_playback() function for additional information.
    */
    if( nJRec==0
     && pPager->journalHdr+JOURNAL_HDR_SZ(pPager)==pPager->journalOff
    ){
      nJRec = (u32)((szJ - pPager->journalOff)/JOURNAL_PG_SZ(pPager));
    }
    for(ii=0; rc==SQLITE_OK && ii<nJRec && pPager->journalOff<szJ; ii++){
      rc = pager_playback_one_page(pPager, &pPager->journalOff, pDone, 1, 1);
    }
    assert( rc!=SQLITE_DONE );
  }
  assert( rc!=SQLITE_OK || pPager->journalOff>=szJ );

  /* Finally,  rollback pages from the sub-journal.  Page that were
  ** previously rolled back out of the main journal (and are hence in pDone)
  ** will be skipped.  Out-of-range pages are also skipped.
  */
  if( pSavepoint ){
    u32 ii;            /* Loop counter */
    i64 offset = (i64)pSavepoint->iSubRec*(4+pPager->pageSize);

    if( pagerUseWal(pPager) ){
      rc = sqlite3WalSavepointUndo(pPager->pWal, pSavepoint->aWalData);
    }
    for(ii=pSavepoint->iSubRec; rc==SQLITE_OK && ii<pPager->nSubRec; ii++){
      assert( offset==(i64)ii*(4+pPager->pageSize) );
      rc = pager_playback_one_page(pPager, &offset, pDone, 0, 1);
    }
    assert( rc!=SQLITE_DONE );
  }

  sqlite3BitvecDestroy(pDone);
  if( rc==SQLITE_OK ){
    pPager->journalOff = szJ;
  }

  return rc;
}