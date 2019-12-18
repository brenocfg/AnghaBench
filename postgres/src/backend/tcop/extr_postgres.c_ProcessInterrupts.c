#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ClientAuthInProgress ; 
 scalar_t__ ClientConnectionLost ; 
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ DestNone ; 
 scalar_t__ DestRemote ; 
 scalar_t__ DoingCommandRead ; 
 int /*<<< orphan*/  ERRCODE_ADMIN_SHUTDOWN ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  ERRCODE_DATABASE_DROPPED ; 
 int /*<<< orphan*/  ERRCODE_IDLE_IN_TRANSACTION_SESSION_TIMEOUT ; 
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERRCODE_QUERY_CANCELED ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  HandleParallelMessages () ; 
 scalar_t__ IdleInTransactionSessionTimeout ; 
 int IdleInTransactionSessionTimeoutPending ; 
 scalar_t__ InterruptHoldoffCount ; 
 int InterruptPending ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 scalar_t__ IsLogicalLauncher () ; 
 scalar_t__ IsLogicalWorker () ; 
 int /*<<< orphan*/  LOCK_TIMEOUT ; 
 int /*<<< orphan*/  LockErrorCleanup () ; 
 scalar_t__ PROCSIG_RECOVERY_CONFLICT_DATABASE ; 
 scalar_t__ ParallelMessagePending ; 
 int ProcDiePending ; 
 scalar_t__ QueryCancelHoldoffCount ; 
 int QueryCancelPending ; 
 int RecoveryConflictPending ; 
 scalar_t__ RecoveryConflictReason ; 
 scalar_t__ RecoveryConflictRetryable ; 
 int /*<<< orphan*/  STATEMENT_TIMEOUT ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_recovery_conflict () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_timeout_finish_time (int /*<<< orphan*/ ) ; 
 int get_timeout_indicator (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgstat_report_recovery_conflict (scalar_t__) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 scalar_t__ whereToSendOutput ; 

void
ProcessInterrupts(void)
{
	/* OK to accept any interrupts now? */
	if (InterruptHoldoffCount != 0 || CritSectionCount != 0)
		return;
	InterruptPending = false;

	if (ProcDiePending)
	{
		ProcDiePending = false;
		QueryCancelPending = false; /* ProcDie trumps QueryCancel */
		LockErrorCleanup();
		/* As in quickdie, don't risk sending to client during auth */
		if (ClientAuthInProgress && whereToSendOutput == DestRemote)
			whereToSendOutput = DestNone;
		if (ClientAuthInProgress)
			ereport(FATAL,
					(errcode(ERRCODE_QUERY_CANCELED),
					 errmsg("canceling authentication due to timeout")));
		else if (IsAutoVacuumWorkerProcess())
			ereport(FATAL,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("terminating autovacuum process due to administrator command")));
		else if (IsLogicalWorker())
			ereport(FATAL,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("terminating logical replication worker due to administrator command")));
		else if (IsLogicalLauncher())
		{
			ereport(DEBUG1,
					(errmsg("logical replication launcher shutting down")));

			/*
			 * The logical replication launcher can be stopped at any time.
			 * Use exit status 1 so the background worker is restarted.
			 */
			proc_exit(1);
		}
		else if (RecoveryConflictPending && RecoveryConflictRetryable)
		{
			pgstat_report_recovery_conflict(RecoveryConflictReason);
			ereport(FATAL,
					(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
					 errmsg("terminating connection due to conflict with recovery"),
					 errdetail_recovery_conflict()));
		}
		else if (RecoveryConflictPending)
		{
			/* Currently there is only one non-retryable recovery conflict */
			Assert(RecoveryConflictReason == PROCSIG_RECOVERY_CONFLICT_DATABASE);
			pgstat_report_recovery_conflict(RecoveryConflictReason);
			ereport(FATAL,
					(errcode(ERRCODE_DATABASE_DROPPED),
					 errmsg("terminating connection due to conflict with recovery"),
					 errdetail_recovery_conflict()));
		}
		else
			ereport(FATAL,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("terminating connection due to administrator command")));
	}
	if (ClientConnectionLost)
	{
		QueryCancelPending = false; /* lost connection trumps QueryCancel */
		LockErrorCleanup();
		/* don't send to client, we already know the connection to be dead. */
		whereToSendOutput = DestNone;
		ereport(FATAL,
				(errcode(ERRCODE_CONNECTION_FAILURE),
				 errmsg("connection to client lost")));
	}

	/*
	 * If a recovery conflict happens while we are waiting for input from the
	 * client, the client is presumably just sitting idle in a transaction,
	 * preventing recovery from making progress.  Terminate the connection to
	 * dislodge it.
	 */
	if (RecoveryConflictPending && DoingCommandRead)
	{
		QueryCancelPending = false; /* this trumps QueryCancel */
		RecoveryConflictPending = false;
		LockErrorCleanup();
		pgstat_report_recovery_conflict(RecoveryConflictReason);
		ereport(FATAL,
				(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
				 errmsg("terminating connection due to conflict with recovery"),
				 errdetail_recovery_conflict(),
				 errhint("In a moment you should be able to reconnect to the"
						 " database and repeat your command.")));
	}

	/*
	 * Don't allow query cancel interrupts while reading input from the
	 * client, because we might lose sync in the FE/BE protocol.  (Die
	 * interrupts are OK, because we won't read any further messages from the
	 * client in that case.)
	 */
	if (QueryCancelPending && QueryCancelHoldoffCount != 0)
	{
		/*
		 * Re-arm InterruptPending so that we process the cancel request as
		 * soon as we're done reading the message.
		 */
		InterruptPending = true;
	}
	else if (QueryCancelPending)
	{
		bool		lock_timeout_occurred;
		bool		stmt_timeout_occurred;

		QueryCancelPending = false;

		/*
		 * If LOCK_TIMEOUT and STATEMENT_TIMEOUT indicators are both set, we
		 * need to clear both, so always fetch both.
		 */
		lock_timeout_occurred = get_timeout_indicator(LOCK_TIMEOUT, true);
		stmt_timeout_occurred = get_timeout_indicator(STATEMENT_TIMEOUT, true);

		/*
		 * If both were set, we want to report whichever timeout completed
		 * earlier; this ensures consistent behavior if the machine is slow
		 * enough that the second timeout triggers before we get here.  A tie
		 * is arbitrarily broken in favor of reporting a lock timeout.
		 */
		if (lock_timeout_occurred && stmt_timeout_occurred &&
			get_timeout_finish_time(STATEMENT_TIMEOUT) < get_timeout_finish_time(LOCK_TIMEOUT))
			lock_timeout_occurred = false;	/* report stmt timeout */

		if (lock_timeout_occurred)
		{
			LockErrorCleanup();
			ereport(ERROR,
					(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
					 errmsg("canceling statement due to lock timeout")));
		}
		if (stmt_timeout_occurred)
		{
			LockErrorCleanup();
			ereport(ERROR,
					(errcode(ERRCODE_QUERY_CANCELED),
					 errmsg("canceling statement due to statement timeout")));
		}
		if (IsAutoVacuumWorkerProcess())
		{
			LockErrorCleanup();
			ereport(ERROR,
					(errcode(ERRCODE_QUERY_CANCELED),
					 errmsg("canceling autovacuum task")));
		}
		if (RecoveryConflictPending)
		{
			RecoveryConflictPending = false;
			LockErrorCleanup();
			pgstat_report_recovery_conflict(RecoveryConflictReason);
			ereport(ERROR,
					(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
					 errmsg("canceling statement due to conflict with recovery"),
					 errdetail_recovery_conflict()));
		}

		/*
		 * If we are reading a command from the client, just ignore the cancel
		 * request --- sending an extra error message won't accomplish
		 * anything.  Otherwise, go ahead and throw the error.
		 */
		if (!DoingCommandRead)
		{
			LockErrorCleanup();
			ereport(ERROR,
					(errcode(ERRCODE_QUERY_CANCELED),
					 errmsg("canceling statement due to user request")));
		}
	}

	if (IdleInTransactionSessionTimeoutPending)
	{
		/* Has the timeout setting changed since last we looked? */
		if (IdleInTransactionSessionTimeout > 0)
			ereport(FATAL,
					(errcode(ERRCODE_IDLE_IN_TRANSACTION_SESSION_TIMEOUT),
					 errmsg("terminating connection due to idle-in-transaction timeout")));
		else
			IdleInTransactionSessionTimeoutPending = false;

	}

	if (ParallelMessagePending)
		HandleParallelMessages();
}