#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ eState; int journalMode; int errCode; scalar_t__ tempFile; scalar_t__ setMaster; scalar_t__ journalHdr; scalar_t__ journalOff; int /*<<< orphan*/  fd; int /*<<< orphan*/  jfd; scalar_t__ changeCountDone; int /*<<< orphan*/  eLock; int /*<<< orphan*/  exclusiveMode; int /*<<< orphan*/  pWal; scalar_t__ pInJournal; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  MEMDB ; 
 int /*<<< orphan*/  NO_LOCK ; 
 scalar_t__ PAGER_ERROR ; 
 int PAGER_JOURNALMODE_DELETE ; 
 int PAGER_JOURNALMODE_MEMORY ; 
 int PAGER_JOURNALMODE_OFF ; 
 int PAGER_JOURNALMODE_PERSIST ; 
 int PAGER_JOURNALMODE_TRUNCATE ; 
 int PAGER_JOURNALMODE_WAL ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_READER ; 
 int SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNKNOWN_LOCK ; 
 scalar_t__ USEFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 int pagerUnlockDb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pagerUseWal (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  releaseAllSavepoints (TYPE_1__*) ; 
 int /*<<< orphan*/  setGetterMethod (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BitvecDestroy (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int sqlite3OsDeviceCharacteristics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WalEndReadTransaction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pager_unlock(Pager *pPager){

  assert( pPager->eState==PAGER_READER
       || pPager->eState==PAGER_OPEN
       || pPager->eState==PAGER_ERROR
  );

  sqlite3BitvecDestroy(pPager->pInJournal);
  pPager->pInJournal = 0;
  releaseAllSavepoints(pPager);

  if( pagerUseWal(pPager) ){
    assert( !isOpen(pPager->jfd) );
    sqlite3WalEndReadTransaction(pPager->pWal);
    pPager->eState = PAGER_OPEN;
  }else if( !pPager->exclusiveMode ){
    int rc;                       /* Error code returned by pagerUnlockDb() */
    int iDc = isOpen(pPager->fd)?sqlite3OsDeviceCharacteristics(pPager->fd):0;

    /* If the operating system support deletion of open files, then
    ** close the journal file when dropping the database lock.  Otherwise
    ** another connection with journal_mode=delete might delete the file
    ** out from under us.
    */
    assert( (PAGER_JOURNALMODE_MEMORY   & 5)!=1 );
    assert( (PAGER_JOURNALMODE_OFF      & 5)!=1 );
    assert( (PAGER_JOURNALMODE_WAL      & 5)!=1 );
    assert( (PAGER_JOURNALMODE_DELETE   & 5)!=1 );
    assert( (PAGER_JOURNALMODE_TRUNCATE & 5)==1 );
    assert( (PAGER_JOURNALMODE_PERSIST  & 5)==1 );
    if( 0==(iDc & SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN)
     || 1!=(pPager->journalMode & 5)
    ){
      sqlite3OsClose(pPager->jfd);
    }

    /* If the pager is in the ERROR state and the call to unlock the database
    ** file fails, set the current lock to UNKNOWN_LOCK. See the comment
    ** above the #define for UNKNOWN_LOCK for an explanation of why this
    ** is necessary.
    */
    rc = pagerUnlockDb(pPager, NO_LOCK);
    if( rc!=SQLITE_OK && pPager->eState==PAGER_ERROR ){
      pPager->eLock = UNKNOWN_LOCK;
    }

    /* The pager state may be changed from PAGER_ERROR to PAGER_OPEN here
    ** without clearing the error code. This is intentional - the error
    ** code is cleared and the cache reset in the block below.
    */
    assert( pPager->errCode || pPager->eState!=PAGER_ERROR );
    pPager->changeCountDone = 0;
    pPager->eState = PAGER_OPEN;
  }

  /* If Pager.errCode is set, the contents of the pager cache cannot be
  ** trusted. Now that there are no outstanding references to the pager,
  ** it can safely move back to PAGER_OPEN state. This happens in both
  ** normal and exclusive-locking mode.
  */
  assert( pPager->errCode==SQLITE_OK || !MEMDB );
  if( pPager->errCode ){
    if( pPager->tempFile==0 ){
      pager_reset(pPager);
      pPager->changeCountDone = 0;
      pPager->eState = PAGER_OPEN;
    }else{
      pPager->eState = (isOpen(pPager->jfd) ? PAGER_OPEN : PAGER_READER);
    }
    if( USEFETCH(pPager) ) sqlite3OsUnfetch(pPager->fd, 0, 0);
    pPager->errCode = SQLITE_OK;
    setGetterMethod(pPager);
  }

  pPager->journalOff = 0;
  pPager->journalHdr = 0;
  pPager->setMaster = 0;
}