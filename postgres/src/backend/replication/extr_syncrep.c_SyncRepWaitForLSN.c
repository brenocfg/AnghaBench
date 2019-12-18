#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_4__ {scalar_t__ syncRepState; scalar_t__ waitLSN; int /*<<< orphan*/  syncRepLinks; } ;
struct TYPE_3__ {scalar_t__* lsn; int /*<<< orphan*/  sync_standbys_defined; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DestNone ; 
 int /*<<< orphan*/  ERRCODE_ADMIN_SHUTDOWN ; 
 scalar_t__ InterruptHoldoffCount ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_2__* MyProc ; 
 int ProcDiePending ; 
 int QueryCancelPending ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int SHMQueueIsDetached (int /*<<< orphan*/ *) ; 
 scalar_t__ SYNC_REP_NOT_WAITING ; 
 scalar_t__ SYNC_REP_WAITING ; 
 scalar_t__ SYNC_REP_WAIT_COMPLETE ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_FLUSH ; 
 int /*<<< orphan*/  SyncRepCancelWait () ; 
 int /*<<< orphan*/  SyncRepLock ; 
 int /*<<< orphan*/  SyncRepQueueInsert (int) ; 
 int SyncRepQueueIsOrderedByLSN (int) ; 
 int /*<<< orphan*/  SyncRepRequested () ; 
 int SyncRepWaitMode ; 
 int /*<<< orphan*/  WAIT_EVENT_SYNC_REP ; 
 int /*<<< orphan*/  WARNING ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WaitLatch (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* WalSndCtl ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_ps_display (int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_read_barrier () ; 
 int /*<<< orphan*/  set_ps_display (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 scalar_t__ update_process_title ; 
 int /*<<< orphan*/  whereToSendOutput ; 

void
SyncRepWaitForLSN(XLogRecPtr lsn, bool commit)
{
	char	   *new_status = NULL;
	const char *old_status;
	int			mode;

	/*
	 * This should be called while holding interrupts during a transaction
	 * commit to prevent the follow-up shared memory queue cleanups to be
	 * influenced by external interruptions.
	 */
	Assert(InterruptHoldoffCount > 0);

	/* Cap the level for anything other than commit to remote flush only. */
	if (commit)
		mode = SyncRepWaitMode;
	else
		mode = Min(SyncRepWaitMode, SYNC_REP_WAIT_FLUSH);

	/*
	 * Fast exit if user has not requested sync replication.
	 */
	if (!SyncRepRequested())
		return;

	Assert(SHMQueueIsDetached(&(MyProc->syncRepLinks)));
	Assert(WalSndCtl != NULL);

	LWLockAcquire(SyncRepLock, LW_EXCLUSIVE);
	Assert(MyProc->syncRepState == SYNC_REP_NOT_WAITING);

	/*
	 * We don't wait for sync rep if WalSndCtl->sync_standbys_defined is not
	 * set.  See SyncRepUpdateSyncStandbysDefined.
	 *
	 * Also check that the standby hasn't already replied. Unlikely race
	 * condition but we'll be fetching that cache line anyway so it's likely
	 * to be a low cost check.
	 */
	if (!WalSndCtl->sync_standbys_defined ||
		lsn <= WalSndCtl->lsn[mode])
	{
		LWLockRelease(SyncRepLock);
		return;
	}

	/*
	 * Set our waitLSN so WALSender will know when to wake us, and add
	 * ourselves to the queue.
	 */
	MyProc->waitLSN = lsn;
	MyProc->syncRepState = SYNC_REP_WAITING;
	SyncRepQueueInsert(mode);
	Assert(SyncRepQueueIsOrderedByLSN(mode));
	LWLockRelease(SyncRepLock);

	/* Alter ps display to show waiting for sync rep. */
	if (update_process_title)
	{
		int			len;

		old_status = get_ps_display(&len);
		new_status = (char *) palloc(len + 32 + 1);
		memcpy(new_status, old_status, len);
		sprintf(new_status + len, " waiting for %X/%X",
				(uint32) (lsn >> 32), (uint32) lsn);
		set_ps_display(new_status, false);
		new_status[len] = '\0'; /* truncate off " waiting ..." */
	}

	/*
	 * Wait for specified LSN to be confirmed.
	 *
	 * Each proc has its own wait latch, so we perform a normal latch
	 * check/wait loop here.
	 */
	for (;;)
	{
		int			rc;

		/* Must reset the latch before testing state. */
		ResetLatch(MyLatch);

		/*
		 * Acquiring the lock is not needed, the latch ensures proper
		 * barriers. If it looks like we're done, we must really be done,
		 * because once walsender changes the state to SYNC_REP_WAIT_COMPLETE,
		 * it will never update it again, so we can't be seeing a stale value
		 * in that case.
		 */
		if (MyProc->syncRepState == SYNC_REP_WAIT_COMPLETE)
			break;

		/*
		 * If a wait for synchronous replication is pending, we can neither
		 * acknowledge the commit nor raise ERROR or FATAL.  The latter would
		 * lead the client to believe that the transaction aborted, which is
		 * not true: it's already committed locally. The former is no good
		 * either: the client has requested synchronous replication, and is
		 * entitled to assume that an acknowledged commit is also replicated,
		 * which might not be true. So in this case we issue a WARNING (which
		 * some clients may be able to interpret) and shut off further output.
		 * We do NOT reset ProcDiePending, so that the process will die after
		 * the commit is cleaned up.
		 */
		if (ProcDiePending)
		{
			ereport(WARNING,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("canceling the wait for synchronous replication and terminating connection due to administrator command"),
					 errdetail("The transaction has already committed locally, but might not have been replicated to the standby.")));
			whereToSendOutput = DestNone;
			SyncRepCancelWait();
			break;
		}

		/*
		 * It's unclear what to do if a query cancel interrupt arrives.  We
		 * can't actually abort at this point, but ignoring the interrupt
		 * altogether is not helpful, so we just terminate the wait with a
		 * suitable warning.
		 */
		if (QueryCancelPending)
		{
			QueryCancelPending = false;
			ereport(WARNING,
					(errmsg("canceling wait for synchronous replication due to user request"),
					 errdetail("The transaction has already committed locally, but might not have been replicated to the standby.")));
			SyncRepCancelWait();
			break;
		}

		/*
		 * Wait on latch.  Any condition that should wake us up will set the
		 * latch, so no need for timeout.
		 */
		rc = WaitLatch(MyLatch, WL_LATCH_SET | WL_POSTMASTER_DEATH, -1,
					   WAIT_EVENT_SYNC_REP);

		/*
		 * If the postmaster dies, we'll probably never get an acknowledgment,
		 * because all the wal sender processes will exit. So just bail out.
		 */
		if (rc & WL_POSTMASTER_DEATH)
		{
			ProcDiePending = true;
			whereToSendOutput = DestNone;
			SyncRepCancelWait();
			break;
		}
	}

	/*
	 * WalSender has checked our LSN and has removed us from queue. Clean up
	 * state and leave.  It's OK to reset these shared memory fields without
	 * holding SyncRepLock, because any walsenders will ignore us anyway when
	 * we're not on the queue.  We need a read barrier to make sure we see the
	 * changes to the queue link (this might be unnecessary without
	 * assertions, but better safe than sorry).
	 */
	pg_read_barrier();
	Assert(SHMQueueIsDetached(&(MyProc->syncRepLinks)));
	MyProc->syncRepState = SYNC_REP_NOT_WAITING;
	MyProc->waitLSN = 0;

	if (new_status)
	{
		/* Reset ps display */
		set_ps_display(new_status, false);
		pfree(new_status);
	}
}