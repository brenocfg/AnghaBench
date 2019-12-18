#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_16__ {scalar_t__ mxPathname; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  scalar_t__ i64 ;
struct TYPE_18__ {scalar_t__ pMethods; } ;
struct TYPE_17__ {char* pTmpSpace; scalar_t__ journalOff; scalar_t__ journalHdr; scalar_t__ eState; int /*<<< orphan*/  zJournal; TYPE_1__* pVfs; int /*<<< orphan*/  jfd; int /*<<< orphan*/  tempFile; int /*<<< orphan*/  changeCountDone; TYPE_4__* fd; int /*<<< orphan*/  dbSize; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ JOURNAL_HDR_SZ (TYPE_2__*) ; 
 scalar_t__ JOURNAL_PG_SZ (TYPE_2__*) ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_WRITER_DBMOD ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_FCNTL_DB_UNCHANGED ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int /*<<< orphan*/  SQLITE_NOTICE_RECOVER_ROLLBACK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int isOpen (int /*<<< orphan*/ ) ; 
 int pager_delmaster (TYPE_2__*,char*) ; 
 int pager_end_transaction (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int pager_playback_one_page (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pager_reset (TYPE_2__*) ; 
 int pager_truncate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int readJournalHdr (TYPE_2__*,int,scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int readMasterJournal (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  setSectorSize (TYPE_2__*) ; 
 int sqlite3OsAccess (TYPE_1__*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3OsFileControlHint (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsFileSize (int /*<<< orphan*/ ,scalar_t__*) ; 
 int sqlite3PagerSync (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int pager_playback(Pager *pPager, int isHot){
  sqlite3_vfs *pVfs = pPager->pVfs;
  i64 szJ;                 /* Size of the journal file in bytes */
  u32 nRec;                /* Number of Records in the journal */
  u32 u;                   /* Unsigned loop counter */
  Pgno mxPg = 0;           /* Size of the original file in pages */
  int rc;                  /* Result code of a subroutine */
  int res = 1;             /* Value returned by sqlite3OsAccess() */
  char *zMaster = 0;       /* Name of master journal file if any */
  int needPagerReset;      /* True to reset page prior to first page rollback */
  int nPlayback = 0;       /* Total number of pages restored from journal */

  /* Figure out how many records are in the journal.  Abort early if
  ** the journal is empty.
  */
  assert( isOpen(pPager->jfd) );
  rc = sqlite3OsFileSize(pPager->jfd, &szJ);
  if( rc!=SQLITE_OK ){
    goto end_playback;
  }

  /* Read the master journal name from the journal, if it is present.
  ** If a master journal file name is specified, but the file is not
  ** present on disk, then the journal is not hot and does not need to be
  ** played back.
  **
  ** TODO: Technically the following is an error because it assumes that
  ** buffer Pager.pTmpSpace is (mxPathname+1) bytes or larger. i.e. that
  ** (pPager->pageSize >= pPager->pVfs->mxPathname+1). Using os_unix.c,
  **  mxPathname is 512, which is the same as the minimum allowable value
  ** for pageSize.
  */
  zMaster = pPager->pTmpSpace;
  rc = readMasterJournal(pPager->jfd, zMaster, pPager->pVfs->mxPathname+1);
  if( rc==SQLITE_OK && zMaster[0] ){
    rc = sqlite3OsAccess(pVfs, zMaster, SQLITE_ACCESS_EXISTS, &res);
  }
  zMaster = 0;
  if( rc!=SQLITE_OK || !res ){
    goto end_playback;
  }
  pPager->journalOff = 0;
  needPagerReset = isHot;

  /* This loop terminates either when a readJournalHdr() or 
  ** pager_playback_one_page() call returns SQLITE_DONE or an IO error 
  ** occurs. 
  */
  while( 1 ){
    /* Read the next journal header from the journal file.  If there are
    ** not enough bytes left in the journal file for a complete header, or
    ** it is corrupted, then a process must have failed while writing it.
    ** This indicates nothing more needs to be rolled back.
    */
    rc = readJournalHdr(pPager, isHot, szJ, &nRec, &mxPg);
    if( rc!=SQLITE_OK ){ 
      if( rc==SQLITE_DONE ){
        rc = SQLITE_OK;
      }
      goto end_playback;
    }

    /* If nRec is 0xffffffff, then this journal was created by a process
    ** working in no-sync mode. This means that the rest of the journal
    ** file consists of pages, there are no more journal headers. Compute
    ** the value of nRec based on this assumption.
    */
    if( nRec==0xffffffff ){
      assert( pPager->journalOff==JOURNAL_HDR_SZ(pPager) );
      nRec = (int)((szJ - JOURNAL_HDR_SZ(pPager))/JOURNAL_PG_SZ(pPager));
    }

    /* If nRec is 0 and this rollback is of a transaction created by this
    ** process and if this is the final header in the journal, then it means
    ** that this part of the journal was being filled but has not yet been
    ** synced to disk.  Compute the number of pages based on the remaining
    ** size of the file.
    **
    ** The third term of the test was added to fix ticket #2565.
    ** When rolling back a hot journal, nRec==0 always means that the next
    ** chunk of the journal contains zero pages to be rolled back.  But
    ** when doing a ROLLBACK and the nRec==0 chunk is the last chunk in
    ** the journal, it means that the journal might contain additional
    ** pages that need to be rolled back and that the number of pages 
    ** should be computed based on the journal file size.
    */
    if( nRec==0 && !isHot &&
        pPager->journalHdr+JOURNAL_HDR_SZ(pPager)==pPager->journalOff ){
      nRec = (int)((szJ - pPager->journalOff) / JOURNAL_PG_SZ(pPager));
    }

    /* If this is the first header read from the journal, truncate the
    ** database file back to its original size.
    */
    if( pPager->journalOff==JOURNAL_HDR_SZ(pPager) ){
      rc = pager_truncate(pPager, mxPg);
      if( rc!=SQLITE_OK ){
        goto end_playback;
      }
      pPager->dbSize = mxPg;
    }

    /* Copy original pages out of the journal and back into the 
    ** database file and/or page cache.
    */
    for(u=0; u<nRec; u++){
      if( needPagerReset ){
        pager_reset(pPager);
        needPagerReset = 0;
      }
      rc = pager_playback_one_page(pPager,&pPager->journalOff,0,1,0);
      if( rc==SQLITE_OK ){
        nPlayback++;
      }else{
        if( rc==SQLITE_DONE ){
          pPager->journalOff = szJ;
          break;
        }else if( rc==SQLITE_IOERR_SHORT_READ ){
          /* If the journal has been truncated, simply stop reading and
          ** processing the journal. This might happen if the journal was
          ** not completely written and synced prior to a crash.  In that
          ** case, the database should have never been written in the
          ** first place so it is OK to simply abandon the rollback. */
          rc = SQLITE_OK;
          goto end_playback;
        }else{
          /* If we are unable to rollback, quit and return the error
          ** code.  This will cause the pager to enter the error state
          ** so that no further harm will be done.  Perhaps the next
          ** process to come along will be able to rollback the database.
          */
          goto end_playback;
        }
      }
    }
  }
  /*NOTREACHED*/
  assert( 0 );

end_playback:
  /* Following a rollback, the database file should be back in its original
  ** state prior to the start of the transaction, so invoke the
  ** SQLITE_FCNTL_DB_UNCHANGED file-control method to disable the
  ** assertion that the transaction counter was modified.
  */
#ifdef SQLITE_DEBUG
  if( pPager->fd->pMethods ){
    sqlite3OsFileControlHint(pPager->fd,SQLITE_FCNTL_DB_UNCHANGED,0);
  }
#endif

  /* If this playback is happening automatically as a result of an IO or 
  ** malloc error that occurred after the change-counter was updated but 
  ** before the transaction was committed, then the change-counter 
  ** modification may just have been reverted. If this happens in exclusive 
  ** mode, then subsequent transactions performed by the connection will not
  ** update the change-counter at all. This may lead to cache inconsistency
  ** problems for other processes at some point in the future. So, just
  ** in case this has happened, clear the changeCountDone flag now.
  */
  pPager->changeCountDone = pPager->tempFile;

  if( rc==SQLITE_OK ){
    zMaster = pPager->pTmpSpace;
    rc = readMasterJournal(pPager->jfd, zMaster, pPager->pVfs->mxPathname+1);
    testcase( rc!=SQLITE_OK );
  }
  if( rc==SQLITE_OK
   && (pPager->eState>=PAGER_WRITER_DBMOD || pPager->eState==PAGER_OPEN)
  ){
    rc = sqlite3PagerSync(pPager);
  }
  if( rc==SQLITE_OK ){
    rc = pager_end_transaction(pPager, zMaster[0]!='\0', 0);
    testcase( rc!=SQLITE_OK );
  }
  if( rc==SQLITE_OK && zMaster[0] && res ){
    /* If there was a master journal and this routine will return success,
    ** see if it is possible to delete the master journal.
    */
    rc = pager_delmaster(pPager, zMaster);
    testcase( rc!=SQLITE_OK );
  }
  if( isHot && nPlayback ){
    sqlite3_log(SQLITE_NOTICE_RECOVER_ROLLBACK, "recovered %d pages from %s",
                nPlayback, pPager->zJournal);
  }

  /* The Pager.sectorSize variable may have been updated while rolling
  ** back a journal created by a process with a different sector size
  ** value. Reset it to the correct value for this process.
  */
  setSectorSize(pPager);
  return rc;
}