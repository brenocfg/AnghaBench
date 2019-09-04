#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  WalIterator ;
struct TYPE_15__ {scalar_t__ nBackfill; scalar_t__* aReadMark; } ;
typedef  TYPE_2__ WalCkptInfo ;
struct TYPE_14__ {scalar_t__ mxFrame; scalar_t__ nPage; } ;
struct TYPE_16__ {int writeLock; TYPE_1__ hdr; int /*<<< orphan*/  pDbFd; int /*<<< orphan*/  pWalFd; } ;
typedef  TYPE_3__ Wal ;
struct TYPE_17__ {scalar_t__ mxFrame; } ;

/* Variables and functions */
 int IS_BIG_INT (int) ; 
 scalar_t__ READMARK_NOT_USED ; 
 int SQLITE_BUSY ; 
 int SQLITE_CHECKPOINT_PASSIVE ; 
 int SQLITE_CHECKPOINT_RESTART ; 
 int /*<<< orphan*/  SQLITE_FCNTL_SIZE_HINT ; 
 int SQLITE_OK ; 
 int WAL_FRAME_HDRSIZE ; 
 int WAL_NREADER ; 
 int /*<<< orphan*/  WAL_READ_LOCK (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3OsFileControlHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sqlite3OsFileSize (int /*<<< orphan*/ ,int*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int sqlite3OsSync (int /*<<< orphan*/ ,int) ; 
 int sqlite3OsTruncate (int /*<<< orphan*/ ,int) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int walBusyLock (TYPE_3__*,int (*) (void*),void*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* walCkptInfo (TYPE_3__*) ; 
 int walFrameOffset (scalar_t__,int) ; 
 scalar_t__ walFramePgno (TYPE_3__*,scalar_t__) ; 
 TYPE_7__* walIndexHdr (TYPE_3__*) ; 
 int /*<<< orphan*/  walIteratorFree (int /*<<< orphan*/ *) ; 
 int walIteratorInit (TYPE_3__*,int /*<<< orphan*/ **) ; 
 scalar_t__ walIteratorNext (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int walPagesize (TYPE_3__*) ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int walCheckpoint(
  Wal *pWal,                      /* Wal connection */
  int eMode,                      /* One of PASSIVE, FULL or RESTART */
  int (*xBusyCall)(void*),        /* Function to call when busy */
  void *pBusyArg,                 /* Context argument for xBusyHandler */
  int sync_flags,                 /* Flags for OsSync() (or 0) */
  u8 *zBuf                        /* Temporary buffer to use */
){
  int rc;                         /* Return code */
  int szPage;                     /* Database page-size */
  WalIterator *pIter = 0;         /* Wal iterator context */
  u32 iDbpage = 0;                /* Next database page to write */
  u32 iFrame = 0;                 /* Wal frame containing data for iDbpage */
  u32 mxSafeFrame;                /* Max frame that can be backfilled */
  u32 mxPage;                     /* Max database page to write */
  int i;                          /* Loop counter */
  volatile WalCkptInfo *pInfo;    /* The checkpoint status information */
  int (*xBusy)(void*) = 0;        /* Function to call when waiting for locks */

  szPage = walPagesize(pWal);
  testcase( szPage<=32768 );
  testcase( szPage>=65536 );
  pInfo = walCkptInfo(pWal);
  if( pInfo->nBackfill>=pWal->hdr.mxFrame ) return SQLITE_OK;

  /* Allocate the iterator */
  rc = walIteratorInit(pWal, &pIter);
  if( rc!=SQLITE_OK ){
    return rc;
  }
  assert( pIter );

  if( eMode!=SQLITE_CHECKPOINT_PASSIVE ) xBusy = xBusyCall;

  /* Compute in mxSafeFrame the index of the last frame of the WAL that is
  ** safe to write into the database.  Frames beyond mxSafeFrame might
  ** overwrite database pages that are in use by active readers and thus
  ** cannot be backfilled from the WAL.
  */
  mxSafeFrame = pWal->hdr.mxFrame;
  mxPage = pWal->hdr.nPage;
  for(i=1; i<WAL_NREADER; i++){
    u32 y = pInfo->aReadMark[i];
    if( mxSafeFrame>y ){
      assert( y<=pWal->hdr.mxFrame );
      rc = walBusyLock(pWal, xBusy, pBusyArg, WAL_READ_LOCK(i), 1);
      if( rc==SQLITE_OK ){
        pInfo->aReadMark[i] = (i==1 ? mxSafeFrame : READMARK_NOT_USED);
        walUnlockExclusive(pWal, WAL_READ_LOCK(i), 1);
      }else if( rc==SQLITE_BUSY ){
        mxSafeFrame = y;
        xBusy = 0;
      }else{
        goto walcheckpoint_out;
      }
    }
  }

  if( pInfo->nBackfill<mxSafeFrame
   && (rc = walBusyLock(pWal, xBusy, pBusyArg, WAL_READ_LOCK(0), 1))==SQLITE_OK
  ){
    i64 nSize;                    /* Current size of database file */
    u32 nBackfill = pInfo->nBackfill;

    /* Sync the WAL to disk */
    if( sync_flags ){
      rc = sqlite3OsSync(pWal->pWalFd, sync_flags);
    }

    /* If the database may grow as a result of this checkpoint, hint
    ** about the eventual size of the db file to the VFS layer.
    */
    if( rc==SQLITE_OK ){
      i64 nReq = ((i64)mxPage * szPage);
      rc = sqlite3OsFileSize(pWal->pDbFd, &nSize);
      if( rc==SQLITE_OK && nSize<nReq ){
        sqlite3OsFileControlHint(pWal->pDbFd, SQLITE_FCNTL_SIZE_HINT, &nReq);
      }
    }


    /* Iterate through the contents of the WAL, copying data to the db file. */
    while( rc==SQLITE_OK && 0==walIteratorNext(pIter, &iDbpage, &iFrame) ){
      i64 iOffset;
      assert( walFramePgno(pWal, iFrame)==iDbpage );
      if( iFrame<=nBackfill || iFrame>mxSafeFrame || iDbpage>mxPage ) continue;
      iOffset = walFrameOffset(iFrame, szPage) + WAL_FRAME_HDRSIZE;
      /* testcase( IS_BIG_INT(iOffset) ); // requires a 4GiB WAL file */
      rc = sqlite3OsRead(pWal->pWalFd, zBuf, szPage, iOffset);
      if( rc!=SQLITE_OK ) break;
      iOffset = (iDbpage-1)*(i64)szPage;
      testcase( IS_BIG_INT(iOffset) );
      rc = sqlite3OsWrite(pWal->pDbFd, zBuf, szPage, iOffset);
      if( rc!=SQLITE_OK ) break;
    }

    /* If work was actually accomplished... */
    if( rc==SQLITE_OK ){
      if( mxSafeFrame==walIndexHdr(pWal)->mxFrame ){
        i64 szDb = pWal->hdr.nPage*(i64)szPage;
        testcase( IS_BIG_INT(szDb) );
        rc = sqlite3OsTruncate(pWal->pDbFd, szDb);
        if( rc==SQLITE_OK && sync_flags ){
          rc = sqlite3OsSync(pWal->pDbFd, sync_flags);
        }
      }
      if( rc==SQLITE_OK ){
        pInfo->nBackfill = mxSafeFrame;
      }
    }

    /* Release the reader lock held while backfilling */
    walUnlockExclusive(pWal, WAL_READ_LOCK(0), 1);
  }

  if( rc==SQLITE_BUSY ){
    /* Reset the return code so as not to report a checkpoint failure
    ** just because there are active readers.  */
    rc = SQLITE_OK;
  }

  /* If this is an SQLITE_CHECKPOINT_RESTART operation, and the entire wal
  ** file has been copied into the database file, then block until all
  ** readers have finished using the wal file. This ensures that the next
  ** process to write to the database restarts the wal file.
  */
  if( rc==SQLITE_OK && eMode!=SQLITE_CHECKPOINT_PASSIVE ){
    assert( pWal->writeLock );
    if( pInfo->nBackfill<pWal->hdr.mxFrame ){
      rc = SQLITE_BUSY;
    }else if( eMode==SQLITE_CHECKPOINT_RESTART ){
      assert( mxSafeFrame==pWal->hdr.mxFrame );
      rc = walBusyLock(pWal, xBusy, pBusyArg, WAL_READ_LOCK(1), WAL_NREADER-1);
      if( rc==SQLITE_OK ){
        walUnlockExclusive(pWal, WAL_READ_LOCK(1), WAL_NREADER-1);
      }
    }
  }

 walcheckpoint_out:
  walIteratorFree(pIter);
  return rc;
}