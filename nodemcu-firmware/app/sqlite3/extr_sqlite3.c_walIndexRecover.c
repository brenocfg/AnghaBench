#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  WalIndexHdr ;
struct TYPE_13__ {int nBackfillAttempted; int* aReadMark; scalar_t__ nBackfill; } ;
typedef  TYPE_1__ WalCkptInfo ;
struct TYPE_12__ {scalar_t__ bigEndCksum; int* aFrameCksum; int mxFrame; int nPage; scalar_t__ szPage; int /*<<< orphan*/  aSalt; } ;
struct TYPE_14__ {int ckptLock; int writeLock; int szPage; int /*<<< orphan*/  zWalName; TYPE_11__ hdr; int /*<<< orphan*/  pWalFd; void* nCkpt; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 int READMARK_NOT_USED ; 
 scalar_t__ SQLITE_BIGENDIAN ; 
 int SQLITE_CANTOPEN_BKPT ; 
 int SQLITE_MAX_PAGE_SIZE ; 
 int SQLITE_NOMEM_BKPT ; 
 int /*<<< orphan*/  SQLITE_NOTICE_RECOVER_WAL ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_NLOCK ; 
 int /*<<< orphan*/  WALTRACE (char*) ; 
 int WAL_ALL_BUT_WRITE ; 
 int WAL_CKPT_LOCK ; 
 int WAL_FRAME_HDRSIZE ; 
 scalar_t__ WAL_HDRSIZE ; 
 int WAL_MAGIC ; 
 int WAL_MAX_VERSION ; 
 int WAL_NREADER ; 
 int WAL_WRITE_LOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 void* sqlite3Get4byte (scalar_t__*) ; 
 int sqlite3OsFileSize (int /*<<< orphan*/ ,scalar_t__*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  walChecksumBytes (int,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* walCkptInfo (TYPE_2__*) ; 
 int walDecodeFrame (TYPE_2__*,int*,int*,scalar_t__*,scalar_t__*) ; 
 int walIndexAppend (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  walIndexWriteHdr (TYPE_2__*) ; 
 int walLockExclusive (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_2__*,int,int) ; 

__attribute__((used)) static int walIndexRecover(Wal *pWal){
  int rc;                         /* Return Code */
  i64 nSize;                      /* Size of log file */
  u32 aFrameCksum[2] = {0, 0};
  int iLock;                      /* Lock offset to lock for checkpoint */
  int nLock;                      /* Number of locks to hold */

  /* Obtain an exclusive lock on all byte in the locking range not already
  ** locked by the caller. The caller is guaranteed to have locked the
  ** WAL_WRITE_LOCK byte, and may have also locked the WAL_CKPT_LOCK byte.
  ** If successful, the same bytes that are locked here are unlocked before
  ** this function returns.
  */
  assert( pWal->ckptLock==1 || pWal->ckptLock==0 );
  assert( WAL_ALL_BUT_WRITE==WAL_WRITE_LOCK+1 );
  assert( WAL_CKPT_LOCK==WAL_ALL_BUT_WRITE );
  assert( pWal->writeLock );
  iLock = WAL_ALL_BUT_WRITE + pWal->ckptLock;
  nLock = SQLITE_SHM_NLOCK - iLock;
  rc = walLockExclusive(pWal, iLock, nLock);
  if( rc ){
    return rc;
  }
  WALTRACE(("WAL%p: recovery begin...\n", pWal));

  memset(&pWal->hdr, 0, sizeof(WalIndexHdr));

  rc = sqlite3OsFileSize(pWal->pWalFd, &nSize);
  if( rc!=SQLITE_OK ){
    goto recovery_error;
  }

  if( nSize>WAL_HDRSIZE ){
    u8 aBuf[WAL_HDRSIZE];         /* Buffer to load WAL header into */
    u8 *aFrame = 0;               /* Malloc'd buffer to load entire frame */
    int szFrame;                  /* Number of bytes in buffer aFrame[] */
    u8 *aData;                    /* Pointer to data part of aFrame buffer */
    int iFrame;                   /* Index of last frame read */
    i64 iOffset;                  /* Next offset to read from log file */
    int szPage;                   /* Page size according to the log */
    u32 magic;                    /* Magic value read from WAL header */
    u32 version;                  /* Magic value read from WAL header */
    int isValid;                  /* True if this frame is valid */

    /* Read in the WAL header. */
    rc = sqlite3OsRead(pWal->pWalFd, aBuf, WAL_HDRSIZE, 0);
    if( rc!=SQLITE_OK ){
      goto recovery_error;
    }

    /* If the database page size is not a power of two, or is greater than
    ** SQLITE_MAX_PAGE_SIZE, conclude that the WAL file contains no valid
    ** data. Similarly, if the 'magic' value is invalid, ignore the whole
    ** WAL file.
    */
    magic = sqlite3Get4byte(&aBuf[0]);
    szPage = sqlite3Get4byte(&aBuf[8]);
    if( (magic&0xFFFFFFFE)!=WAL_MAGIC
     || szPage&(szPage-1)
     || szPage>SQLITE_MAX_PAGE_SIZE
     || szPage<512
    ){
      goto finished;
    }
    pWal->hdr.bigEndCksum = (u8)(magic&0x00000001);
    pWal->szPage = szPage;
    pWal->nCkpt = sqlite3Get4byte(&aBuf[12]);
    memcpy(&pWal->hdr.aSalt, &aBuf[16], 8);

    /* Verify that the WAL header checksum is correct */
    walChecksumBytes(pWal->hdr.bigEndCksum==SQLITE_BIGENDIAN,
        aBuf, WAL_HDRSIZE-2*4, 0, pWal->hdr.aFrameCksum
    );
    if( pWal->hdr.aFrameCksum[0]!=sqlite3Get4byte(&aBuf[24])
     || pWal->hdr.aFrameCksum[1]!=sqlite3Get4byte(&aBuf[28])
    ){
      goto finished;
    }

    /* Verify that the version number on the WAL format is one that
    ** are able to understand */
    version = sqlite3Get4byte(&aBuf[4]);
    if( version!=WAL_MAX_VERSION ){
      rc = SQLITE_CANTOPEN_BKPT;
      goto finished;
    }

    /* Malloc a buffer to read frames into. */
    szFrame = szPage + WAL_FRAME_HDRSIZE;
    aFrame = (u8 *)sqlite3_malloc64(szFrame);
    if( !aFrame ){
      rc = SQLITE_NOMEM_BKPT;
      goto recovery_error;
    }
    aData = &aFrame[WAL_FRAME_HDRSIZE];

    /* Read all frames from the log file. */
    iFrame = 0;
    for(iOffset=WAL_HDRSIZE; (iOffset+szFrame)<=nSize; iOffset+=szFrame){
      u32 pgno;                   /* Database page number for frame */
      u32 nTruncate;              /* dbsize field from frame header */

      /* Read and decode the next log frame. */
      iFrame++;
      rc = sqlite3OsRead(pWal->pWalFd, aFrame, szFrame, iOffset);
      if( rc!=SQLITE_OK ) break;
      isValid = walDecodeFrame(pWal, &pgno, &nTruncate, aData, aFrame);
      if( !isValid ) break;
      rc = walIndexAppend(pWal, iFrame, pgno);
      if( rc!=SQLITE_OK ) break;

      /* If nTruncate is non-zero, this is a commit record. */
      if( nTruncate ){
        pWal->hdr.mxFrame = iFrame;
        pWal->hdr.nPage = nTruncate;
        pWal->hdr.szPage = (u16)((szPage&0xff00) | (szPage>>16));
        testcase( szPage<=32768 );
        testcase( szPage>=65536 );
        aFrameCksum[0] = pWal->hdr.aFrameCksum[0];
        aFrameCksum[1] = pWal->hdr.aFrameCksum[1];
      }
    }

    sqlite3_free(aFrame);
  }

finished:
  if( rc==SQLITE_OK ){
    volatile WalCkptInfo *pInfo;
    int i;
    pWal->hdr.aFrameCksum[0] = aFrameCksum[0];
    pWal->hdr.aFrameCksum[1] = aFrameCksum[1];
    walIndexWriteHdr(pWal);

    /* Reset the checkpoint-header. This is safe because this thread is
    ** currently holding locks that exclude all other readers, writers and
    ** checkpointers.
    */
    pInfo = walCkptInfo(pWal);
    pInfo->nBackfill = 0;
    pInfo->nBackfillAttempted = pWal->hdr.mxFrame;
    pInfo->aReadMark[0] = 0;
    for(i=1; i<WAL_NREADER; i++) pInfo->aReadMark[i] = READMARK_NOT_USED;
    if( pWal->hdr.mxFrame ) pInfo->aReadMark[1] = pWal->hdr.mxFrame;

    /* If more than one frame was recovered from the log file, report an
    ** event via sqlite3_log(). This is to help with identifying performance
    ** problems caused by applications routinely shutting down without
    ** checkpointing the log file.
    */
    if( pWal->hdr.nPage ){
      sqlite3_log(SQLITE_NOTICE_RECOVER_WAL,
          "recovered %d frames from WAL file %s",
          pWal->hdr.mxFrame, pWal->zWalName
      );
    }
  }

recovery_error:
  WALTRACE(("WAL%p: recovery %s\n", pWal, rc ? "failed" : "ok"));
  walUnlockExclusive(pWal, iLock, nLock);
  return rc;
}