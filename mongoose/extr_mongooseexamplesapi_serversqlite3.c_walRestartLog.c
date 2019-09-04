#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_13__ {scalar_t__ nBackfill; int /*<<< orphan*/ * aReadMark; } ;
typedef  TYPE_2__ WalCkptInfo ;
struct TYPE_12__ {scalar_t__ mxFrame; scalar_t__* aSalt; } ;
struct TYPE_14__ {int readLock; TYPE_1__ hdr; int /*<<< orphan*/  nCkpt; } ;
typedef  TYPE_3__ Wal ;

/* Variables and functions */
 int /*<<< orphan*/  READMARK_NOT_USED ; 
 int SQLITE_BUSY ; 
 int SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int SQLITE_PROTOCOL ; 
 int WAL_NREADER ; 
 int /*<<< orphan*/  WAL_READ_LOCK (int) ; 
 int WAL_RETRY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3Get4byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Put4byte (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,scalar_t__*) ; 
 int /*<<< orphan*/  testcase (int) ; 
 TYPE_2__* walCkptInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  walIndexWriteHdr (TYPE_3__*) ; 
 int walLockExclusive (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int walTryBeginRead (TYPE_3__*,int*,int,int) ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walUnlockShared (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int walRestartLog(Wal *pWal){
  int rc = SQLITE_OK;
  int cnt;

  if( pWal->readLock==0 ){
    volatile WalCkptInfo *pInfo = walCkptInfo(pWal);
    assert( pInfo->nBackfill==pWal->hdr.mxFrame );
    if( pInfo->nBackfill>0 ){
      u32 salt1;
      sqlite3_randomness(4, &salt1);
      rc = walLockExclusive(pWal, WAL_READ_LOCK(1), WAL_NREADER-1);
      if( rc==SQLITE_OK ){
        /* If all readers are using WAL_READ_LOCK(0) (in other words if no
        ** readers are currently using the WAL), then the transactions
        ** frames will overwrite the start of the existing log. Update the
        ** wal-index header to reflect this.
        **
        ** In theory it would be Ok to update the cache of the header only
        ** at this point. But updating the actual wal-index header is also
        ** safe and means there is no special case for sqlite3WalUndo()
        ** to handle if this transaction is rolled back.
        */
        int i;                    /* Loop counter */
        u32 *aSalt = pWal->hdr.aSalt;       /* Big-endian salt values */

        pWal->nCkpt++;
        pWal->hdr.mxFrame = 0;
        sqlite3Put4byte((u8*)&aSalt[0], 1 + sqlite3Get4byte((u8*)&aSalt[0]));
        aSalt[1] = salt1;
        walIndexWriteHdr(pWal);
        pInfo->nBackfill = 0;
        pInfo->aReadMark[1] = 0;
        for(i=2; i<WAL_NREADER; i++) pInfo->aReadMark[i] = READMARK_NOT_USED;
        assert( pInfo->aReadMark[0]==0 );
        walUnlockExclusive(pWal, WAL_READ_LOCK(1), WAL_NREADER-1);
      }else if( rc!=SQLITE_BUSY ){
        return rc;
      }
    }
    walUnlockShared(pWal, WAL_READ_LOCK(0));
    pWal->readLock = -1;
    cnt = 0;
    do{
      int notUsed;
      rc = walTryBeginRead(pWal, &notUsed, 1, ++cnt);
    }while( rc==WAL_RETRY );
    assert( (rc&0xff)!=SQLITE_BUSY ); /* BUSY not possible when useWal==1 */
    testcase( (rc&0xff)==SQLITE_IOERR );
    testcase( rc==SQLITE_PROTOCOL );
    testcase( rc==SQLITE_OK );
  }
  return rc;
}