#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TransactionState ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  prevXactReadOnly; int /*<<< orphan*/  nestingLevel; TYPE_1__* parent; int /*<<< orphan*/  subTransactionId; int /*<<< orphan*/  gucNestLevel; scalar_t__ curTransactionOwner; int /*<<< orphan*/  fullTransactionId; scalar_t__ parallelModeLevel; int /*<<< orphan*/  prevSecContext; int /*<<< orphan*/  prevUser; } ;
struct TYPE_4__ {int /*<<< orphan*/  subTransactionId; int /*<<< orphan*/  curTransactionOwner; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortBufferIO () ; 
 int /*<<< orphan*/  AfterTriggerEndSubXact (int) ; 
 int /*<<< orphan*/  AtEOSubXact_ApplyLauncher (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_Files (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_HashTables (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_Inval (int) ; 
 int /*<<< orphan*/  AtEOSubXact_LargeObject (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_Namespace (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_Parallel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_PgStat (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_RelationCache (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_SPI (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOSubXact_on_commit_actions (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_GUC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtSubAbort_Memory () ; 
 int /*<<< orphan*/  AtSubAbort_Notify () ; 
 int /*<<< orphan*/  AtSubAbort_Portals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtSubAbort_ResourceOwner () ; 
 int /*<<< orphan*/  AtSubAbort_Snapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtSubAbort_childXids () ; 
 int /*<<< orphan*/  AtSubAbort_smgr () ; 
 int /*<<< orphan*/  CallSubXactCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 TYPE_2__* CurrentTransactionState ; 
 scalar_t__ FullTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 int /*<<< orphan*/  LockErrorCleanup () ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  RecordTransactionAbort (int) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SUBXACT_EVENT_ABORT_SUB ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 scalar_t__ TRANS_ABORT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  UnlockBuffers () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XLogResetInsertion () ; 
 int /*<<< orphan*/  XactReadOnly ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_end_command () ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  reschedule_timeouts () ; 

__attribute__((used)) static void
AbortSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	/* Prevent cancel/die interrupt while cleaning up */
	HOLD_INTERRUPTS();

	/* Make sure we have a valid memory context and resource owner */
	AtSubAbort_Memory();
	AtSubAbort_ResourceOwner();

	/*
	 * Release any LW locks we might be holding as quickly as possible.
	 * (Regular locks, however, must be held till we finish aborting.)
	 * Releasing LW locks is critical since we might try to grab them again
	 * while cleaning up!
	 *
	 * FIXME This may be incorrect --- Are there some locks we should keep?
	 * Buffer locks, for example?  I don't think so but I'm not sure.
	 */
	LWLockReleaseAll();

	pgstat_report_wait_end();
	pgstat_progress_end_command();
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
	ShowTransactionState("AbortSubTransaction");

	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "AbortSubTransaction while in %s state",
			 TransStateAsString(s->state));

	s->state = TRANS_ABORT;

	/*
	 * Reset user ID which might have been changed transiently.  (See notes in
	 * AbortTransaction.)
	 */
	SetUserIdAndSecContext(s->prevUser, s->prevSecContext);

	/* Exit from parallel mode, if necessary. */
	if (IsInParallelMode())
	{
		AtEOSubXact_Parallel(false, s->subTransactionId);
		s->parallelModeLevel = 0;
	}

	/*
	 * We can skip all this stuff if the subxact failed before creating a
	 * ResourceOwner...
	 */
	if (s->curTransactionOwner)
	{
		AfterTriggerEndSubXact(false);
		AtSubAbort_Portals(s->subTransactionId,
						   s->parent->subTransactionId,
						   s->curTransactionOwner,
						   s->parent->curTransactionOwner);
		AtEOSubXact_LargeObject(false, s->subTransactionId,
								s->parent->subTransactionId);
		AtSubAbort_Notify();

		/* Advertise the fact that we aborted in pg_xact. */
		(void) RecordTransactionAbort(true);

		/* Post-abort cleanup */
		if (FullTransactionIdIsValid(s->fullTransactionId))
			AtSubAbort_childXids();

		CallSubXactCallbacks(SUBXACT_EVENT_ABORT_SUB, s->subTransactionId,
							 s->parent->subTransactionId);

		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_BEFORE_LOCKS,
							 false, false);
		AtEOSubXact_RelationCache(false, s->subTransactionId,
								  s->parent->subTransactionId);
		AtEOSubXact_Inval(false);
		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_LOCKS,
							 false, false);
		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_AFTER_LOCKS,
							 false, false);
		AtSubAbort_smgr();

		AtEOXact_GUC(false, s->gucNestLevel);
		AtEOSubXact_SPI(false, s->subTransactionId);
		AtEOSubXact_on_commit_actions(false, s->subTransactionId,
									  s->parent->subTransactionId);
		AtEOSubXact_Namespace(false, s->subTransactionId,
							  s->parent->subTransactionId);
		AtEOSubXact_Files(false, s->subTransactionId,
						  s->parent->subTransactionId);
		AtEOSubXact_HashTables(false, s->nestingLevel);
		AtEOSubXact_PgStat(false, s->nestingLevel);
		AtSubAbort_Snapshot(s->nestingLevel);
		AtEOSubXact_ApplyLauncher(false, s->nestingLevel);
	}

	/*
	 * Restore the upper transaction's read-only state, too.  This should be
	 * redundant with GUC's cleanup but we may as well do it for consistency
	 * with the commit case.
	 */
	XactReadOnly = s->prevXactReadOnly;

	RESUME_INTERRUPTS();
}