#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_5__ {int* lsn; } ;
typedef  TYPE_1__ WalSndCtlData ;
struct TYPE_7__ {scalar_t__ sync_standby_priority; scalar_t__ state; int /*<<< orphan*/  flush; } ;
struct TYPE_6__ {scalar_t__ syncrep_method; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_4__* MyWalSnd ; 
 scalar_t__ SYNC_REP_PRIORITY ; 
 size_t SYNC_REP_WAIT_APPLY ; 
 size_t SYNC_REP_WAIT_FLUSH ; 
 size_t SYNC_REP_WAIT_WRITE ; 
 TYPE_3__* SyncRepConfig ; 
 int SyncRepGetSyncRecPtr (int*,int*,int*,int*) ; 
 int /*<<< orphan*/  SyncRepLock ; 
 int SyncRepWakeQueue (int,size_t) ; 
 scalar_t__ WALSNDSTATE_STOPPING ; 
 scalar_t__ WALSNDSTATE_STREAMING ; 
 TYPE_1__* WalSndCtl ; 
 scalar_t__ XLogRecPtrIsInvalid (int /*<<< orphan*/ ) ; 
 int announce_next_takeover ; 
 int /*<<< orphan*/  application_name ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 

void
SyncRepReleaseWaiters(void)
{
	volatile WalSndCtlData *walsndctl = WalSndCtl;
	XLogRecPtr	writePtr;
	XLogRecPtr	flushPtr;
	XLogRecPtr	applyPtr;
	bool		got_recptr;
	bool		am_sync;
	int			numwrite = 0;
	int			numflush = 0;
	int			numapply = 0;

	/*
	 * If this WALSender is serving a standby that is not on the list of
	 * potential sync standbys then we have nothing to do. If we are still
	 * starting up, still running base backup or the current flush position is
	 * still invalid, then leave quickly also.  Streaming or stopping WAL
	 * senders are allowed to release waiters.
	 */
	if (MyWalSnd->sync_standby_priority == 0 ||
		(MyWalSnd->state != WALSNDSTATE_STREAMING &&
		 MyWalSnd->state != WALSNDSTATE_STOPPING) ||
		XLogRecPtrIsInvalid(MyWalSnd->flush))
	{
		announce_next_takeover = true;
		return;
	}

	/*
	 * We're a potential sync standby. Release waiters if there are enough
	 * sync standbys and we are considered as sync.
	 */
	LWLockAcquire(SyncRepLock, LW_EXCLUSIVE);

	/*
	 * Check whether we are a sync standby or not, and calculate the synced
	 * positions among all sync standbys.
	 */
	got_recptr = SyncRepGetSyncRecPtr(&writePtr, &flushPtr, &applyPtr, &am_sync);

	/*
	 * If we are managing a sync standby, though we weren't prior to this,
	 * then announce we are now a sync standby.
	 */
	if (announce_next_takeover && am_sync)
	{
		announce_next_takeover = false;

		if (SyncRepConfig->syncrep_method == SYNC_REP_PRIORITY)
			ereport(LOG,
					(errmsg("standby \"%s\" is now a synchronous standby with priority %u",
							application_name, MyWalSnd->sync_standby_priority)));
		else
			ereport(LOG,
					(errmsg("standby \"%s\" is now a candidate for quorum synchronous standby",
							application_name)));
	}

	/*
	 * If the number of sync standbys is less than requested or we aren't
	 * managing a sync standby then just leave.
	 */
	if (!got_recptr || !am_sync)
	{
		LWLockRelease(SyncRepLock);
		announce_next_takeover = !am_sync;
		return;
	}

	/*
	 * Set the lsn first so that when we wake backends they will release up to
	 * this location.
	 */
	if (walsndctl->lsn[SYNC_REP_WAIT_WRITE] < writePtr)
	{
		walsndctl->lsn[SYNC_REP_WAIT_WRITE] = writePtr;
		numwrite = SyncRepWakeQueue(false, SYNC_REP_WAIT_WRITE);
	}
	if (walsndctl->lsn[SYNC_REP_WAIT_FLUSH] < flushPtr)
	{
		walsndctl->lsn[SYNC_REP_WAIT_FLUSH] = flushPtr;
		numflush = SyncRepWakeQueue(false, SYNC_REP_WAIT_FLUSH);
	}
	if (walsndctl->lsn[SYNC_REP_WAIT_APPLY] < applyPtr)
	{
		walsndctl->lsn[SYNC_REP_WAIT_APPLY] = applyPtr;
		numapply = SyncRepWakeQueue(false, SYNC_REP_WAIT_APPLY);
	}

	LWLockRelease(SyncRepLock);

	elog(DEBUG3, "released %d procs up to write %X/%X, %d procs up to flush %X/%X, %d procs up to apply %X/%X",
		 numwrite, (uint32) (writePtr >> 32), (uint32) writePtr,
		 numflush, (uint32) (flushPtr >> 32), (uint32) flushPtr,
		 numapply, (uint32) (applyPtr >> 32), (uint32) applyPtr);
}