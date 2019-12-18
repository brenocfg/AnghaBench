#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_6__ {int /*<<< orphan*/  lxid; } ;
struct TYPE_5__ {scalar_t__ blockState; scalar_t__ state; scalar_t__ parallelModeLevel; int /*<<< orphan*/  prevSecContext; int /*<<< orphan*/  prevUser; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortBufferIO () ; 
 int /*<<< orphan*/  AfterTriggerEndXact (int) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtAbort_Memory () ; 
 int /*<<< orphan*/  AtAbort_Notify () ; 
 int /*<<< orphan*/  AtAbort_Portals () ; 
 int /*<<< orphan*/  AtAbort_ResourceOwner () ; 
 int /*<<< orphan*/  AtAbort_Twophase () ; 
 int /*<<< orphan*/  AtEOXact_ApplyLauncher (int) ; 
 int /*<<< orphan*/  AtEOXact_Buffers (int) ; 
 int /*<<< orphan*/  AtEOXact_ComboCid () ; 
 int /*<<< orphan*/  AtEOXact_Enum () ; 
 int /*<<< orphan*/  AtEOXact_Files (int) ; 
 int /*<<< orphan*/  AtEOXact_GUC (int,int) ; 
 int /*<<< orphan*/  AtEOXact_HashTables (int) ; 
 int /*<<< orphan*/  AtEOXact_Inval (int) ; 
 int /*<<< orphan*/  AtEOXact_LargeObject (int) ; 
 int /*<<< orphan*/  AtEOXact_MultiXact () ; 
 int /*<<< orphan*/  AtEOXact_Namespace (int,int) ; 
 int /*<<< orphan*/  AtEOXact_Parallel (int) ; 
 int /*<<< orphan*/  AtEOXact_PgStat (int,int) ; 
 int /*<<< orphan*/  AtEOXact_RelationCache (int) ; 
 int /*<<< orphan*/  AtEOXact_RelationMap (int,int) ; 
 int /*<<< orphan*/  AtEOXact_SMgr () ; 
 int /*<<< orphan*/  AtEOXact_SPI (int) ; 
 int /*<<< orphan*/  AtEOXact_on_commit_actions (int) ; 
 int /*<<< orphan*/  CallXactCallbacks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 int /*<<< orphan*/  LockErrorCleanup () ; 
 TYPE_2__* MyProc ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcArrayEndTransaction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  RecordTransactionAbort (int) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TBLOCK_PARALLEL_INPROGRESS ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_TRANSACTION_ABORT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANS_ABORT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 scalar_t__ TRANS_PREPARE ; 
 int /*<<< orphan*/ * TopTransactionResourceOwner ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  UnlockBuffers () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XACT_EVENT_ABORT ; 
 int /*<<< orphan*/  XACT_EVENT_PARALLEL_ABORT ; 
 int /*<<< orphan*/  XLogResetInsertion () ; 
 int /*<<< orphan*/  XLogSetAsyncXactLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLastRecEnd ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_end_command () ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_xact_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_timeouts () ; 
 int /*<<< orphan*/  smgrDoPendingDeletes (int) ; 

__attribute__((used)) static void
AbortTransaction(void)
{
	TransactionState s = CurrentTransactionState;
	TransactionId latestXid;
	bool		is_parallel_worker;

	/* Prevent cancel/die interrupt while cleaning up */
	HOLD_INTERRUPTS();

	/* Make sure we have a valid memory context and resource owner */
	AtAbort_Memory();
	AtAbort_ResourceOwner();

	/*
	 * Release any LW locks we might be holding as quickly as possible.
	 * (Regular locks, however, must be held till we finish aborting.)
	 * Releasing LW locks is critical since we might try to grab them again
	 * while cleaning up!
	 */
	LWLockReleaseAll();

	/* Clear wait information and command progress indicator */
	pgstat_report_wait_end();
	pgstat_progress_end_command();

	/* Clean up buffer I/O and buffer context locks, too */
	AbortBufferIO();
	UnlockBuffers();

	/* Reset WAL record construction state */
	XLogResetInsertion();

	/* Cancel condition variable sleep */
	ConditionVariableCancelSleep();

	/*
	 * Also clean up any open wait for lock, since the lock manager will choke
	 * if we try to wait for another lock before doing this.
	 */
	LockErrorCleanup();

	/*
	 * If any timeout events are still active, make sure the timeout interrupt
	 * is scheduled.  This covers possible loss of a timeout interrupt due to
	 * longjmp'ing out of the SIGINT handler (see notes in handle_sig_alarm).
	 * We delay this till after LockErrorCleanup so that we don't uselessly
	 * reschedule lock or deadlock check timeouts.
	 */
	reschedule_timeouts();

	/*
	 * Re-enable signals, in case we got here by longjmp'ing out of a signal
	 * handler.  We do this fairly early in the sequence so that the timeout
	 * infrastructure will be functional if needed while aborting.
	 */
	PG_SETMASK(&UnBlockSig);

	/*
	 * check the current transaction state
	 */
	is_parallel_worker = (s->blockState == TBLOCK_PARALLEL_INPROGRESS);
	if (s->state != TRANS_INPROGRESS && s->state != TRANS_PREPARE)
		elog(WARNING, "AbortTransaction while in %s state",
			 TransStateAsString(s->state));
	Assert(s->parent == NULL);

	/*
	 * set the current transaction state information appropriately during the
	 * abort processing
	 */
	s->state = TRANS_ABORT;

	/*
	 * Reset user ID which might have been changed transiently.  We need this
	 * to clean up in case control escaped out of a SECURITY DEFINER function
	 * or other local change of CurrentUserId; therefore, the prior value of
	 * SecurityRestrictionContext also needs to be restored.
	 *
	 * (Note: it is not necessary to restore session authorization or role
	 * settings here because those can only be changed via GUC, and GUC will
	 * take care of rolling them back if need be.)
	 */
	SetUserIdAndSecContext(s->prevUser, s->prevSecContext);

	/* If in parallel mode, clean up workers and exit parallel mode. */
	if (IsInParallelMode())
	{
		AtEOXact_Parallel(false);
		s->parallelModeLevel = 0;
	}

	/*
	 * do abort processing
	 */
	AfterTriggerEndXact(false); /* 'false' means it's abort */
	AtAbort_Portals();
	AtEOXact_LargeObject(false);
	AtAbort_Notify();
	AtEOXact_RelationMap(false, is_parallel_worker);
	AtAbort_Twophase();

	/*
	 * Advertise the fact that we aborted in pg_xact (assuming that we got as
	 * far as assigning an XID to advertise).  But if we're inside a parallel
	 * worker, skip this; the user backend must be the one to write the abort
	 * record.
	 */
	if (!is_parallel_worker)
		latestXid = RecordTransactionAbort(false);
	else
	{
		latestXid = InvalidTransactionId;

		/*
		 * Since the parallel master won't get our value of XactLastRecEnd in
		 * this case, we nudge WAL-writer ourselves in this case.  See related
		 * comments in RecordTransactionAbort for why this matters.
		 */
		XLogSetAsyncXactLSN(XactLastRecEnd);
	}

	TRACE_POSTGRESQL_TRANSACTION_ABORT(MyProc->lxid);

	/*
	 * Let others know about no transaction in progress by me. Note that this
	 * must be done _before_ releasing locks we hold and _after_
	 * RecordTransactionAbort.
	 */
	ProcArrayEndTransaction(MyProc, latestXid);

	/*
	 * Post-abort cleanup.  See notes in CommitTransaction() concerning
	 * ordering.  We can skip all of it if the transaction failed before
	 * creating a resource owner.
	 */
	if (TopTransactionResourceOwner != NULL)
	{
		if (is_parallel_worker)
			CallXactCallbacks(XACT_EVENT_PARALLEL_ABORT);
		else
			CallXactCallbacks(XACT_EVENT_ABORT);

		ResourceOwnerRelease(TopTransactionResourceOwner,
							 RESOURCE_RELEASE_BEFORE_LOCKS,
							 false, true);
		AtEOXact_Buffers(false);
		AtEOXact_RelationCache(false);
		AtEOXact_Inval(false);
		AtEOXact_MultiXact();
		ResourceOwnerRelease(TopTransactionResourceOwner,
							 RESOURCE_RELEASE_LOCKS,
							 false, true);
		ResourceOwnerRelease(TopTransactionResourceOwner,
							 RESOURCE_RELEASE_AFTER_LOCKS,
							 false, true);
		smgrDoPendingDeletes(false);

		AtEOXact_GUC(false, 1);
		AtEOXact_SPI(false);
		AtEOXact_Enum();
		AtEOXact_on_commit_actions(false);
		AtEOXact_Namespace(false, is_parallel_worker);
		AtEOXact_SMgr();
		AtEOXact_Files(false);
		AtEOXact_ComboCid();
		AtEOXact_HashTables(false);
		AtEOXact_PgStat(false, is_parallel_worker);
		AtEOXact_ApplyLauncher(false);
		pgstat_report_xact_timestamp(0);
	}

	/*
	 * State remains TRANS_ABORT until CleanupTransaction().
	 */
	RESUME_INTERRUPTS();
}