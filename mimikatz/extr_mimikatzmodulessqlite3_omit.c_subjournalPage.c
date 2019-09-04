#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_11__ {scalar_t__ journalMode; int useJournal; scalar_t__ nSubRec; scalar_t__ dbOrigSize; scalar_t__ nSavepoint; int /*<<< orphan*/  pageSize; int /*<<< orphan*/  sjfd; int /*<<< orphan*/  jfd; } ;
struct TYPE_10__ {scalar_t__ pgno; void* pData; TYPE_2__* pPager; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  PAGERID (TYPE_2__*) ; 
 int /*<<< orphan*/  PAGERTRACE (char*) ; 
 scalar_t__ PAGER_JOURNALMODE_OFF ; 
 int SQLITE_OK ; 
 int addToSavepointBitvecs (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 int openSubJournal (TYPE_2__*) ; 
 scalar_t__ pageInJournal (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ pagerUseWal (TYPE_2__*) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int write32bits (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int subjournalPage(PgHdr *pPg){
  int rc = SQLITE_OK;
  Pager *pPager = pPg->pPager;
  if( pPager->journalMode!=PAGER_JOURNALMODE_OFF ){

    /* Open the sub-journal, if it has not already been opened */
    assert( pPager->useJournal );
    assert( isOpen(pPager->jfd) || pagerUseWal(pPager) );
    assert( isOpen(pPager->sjfd) || pPager->nSubRec==0 );
    assert( pagerUseWal(pPager) 
         || pageInJournal(pPager, pPg) 
         || pPg->pgno>pPager->dbOrigSize 
    );
    rc = openSubJournal(pPager);

    /* If the sub-journal was opened successfully (or was already open),
    ** write the journal record into the file.  */
    if( rc==SQLITE_OK ){
      void *pData = pPg->pData;
      i64 offset = (i64)pPager->nSubRec*(4+pPager->pageSize);
      char *pData2;

#if SQLITE_HAS_CODEC   
      if( !pPager->subjInMemory ){
        CODEC2(pPager, pData, pPg->pgno, 7, return SQLITE_NOMEM_BKPT, pData2);
      }else
#endif
      pData2 = pData;
      PAGERTRACE(("STMT-JOURNAL %d page %d\n", PAGERID(pPager), pPg->pgno));
      rc = write32bits(pPager->sjfd, offset, pPg->pgno);
      if( rc==SQLITE_OK ){
        rc = sqlite3OsWrite(pPager->sjfd, pData2, pPager->pageSize, offset+4);
      }
    }
  }
  if( rc==SQLITE_OK ){
    pPager->nSubRec++;
    assert( pPager->nSavepoint>0 );
    rc = addToSavepointBitvecs(pPager, pPg->pgno);
  }
  return rc;
}