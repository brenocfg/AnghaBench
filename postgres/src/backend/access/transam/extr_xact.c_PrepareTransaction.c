#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_3__ {scalar_t__ state; scalar_t__ maxChildXids; scalar_t__ nChildXids; int /*<<< orphan*/ * childXids; scalar_t__ gucNestLevel; scalar_t__ nestingLevel; int /*<<< orphan*/  subTransactionId; void* fullTransactionId; int /*<<< orphan*/ * curTransactionOwner; int /*<<< orphan*/ * parent; } ;
typedef  int /*<<< orphan*/  GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerEndXact (int) ; 
 int /*<<< orphan*/  AfterTriggerFireDeferred () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AtCommit_Memory () ; 
 int /*<<< orphan*/  AtEOXact_Buffers (int) ; 
 int /*<<< orphan*/  AtEOXact_ComboCid () ; 
 int /*<<< orphan*/  AtEOXact_Enum () ; 
 int /*<<< orphan*/  AtEOXact_Files (int) ; 
 int /*<<< orphan*/  AtEOXact_GUC (int,int) ; 
 int /*<<< orphan*/  AtEOXact_HashTables (int) ; 
 int /*<<< orphan*/  AtEOXact_LargeObject (int) ; 
 int /*<<< orphan*/  AtEOXact_Namespace (int,int) ; 
 int /*<<< orphan*/  AtEOXact_RelationCache (int) ; 
 int /*<<< orphan*/  AtEOXact_SMgr () ; 
 int /*<<< orphan*/  AtEOXact_SPI (int) ; 
 int /*<<< orphan*/  AtEOXact_Snapshot (int,int) ; 
 int /*<<< orphan*/  AtEOXact_on_commit_actions (int) ; 
 int /*<<< orphan*/  AtPrepare_Locks () ; 
 int /*<<< orphan*/  AtPrepare_MultiXact () ; 
 int /*<<< orphan*/  AtPrepare_Notify () ; 
 int /*<<< orphan*/  AtPrepare_PgStat () ; 
 int /*<<< orphan*/  AtPrepare_PredicateLocks () ; 
 int /*<<< orphan*/  AtPrepare_RelationMap () ; 
 int /*<<< orphan*/  BufmgrCommit () ; 
 int /*<<< orphan*/  CallXactCallbacks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurTransactionResourceOwner ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EndPrepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  GetCurrentTransactionId () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 void* InvalidFullTransactionId ; 
 int /*<<< orphan*/  InvalidSubTransactionId ; 
 int /*<<< orphan*/  IsInParallelMode () ; 
 int /*<<< orphan*/  MarkAsPreparing (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  MyProc ; 
 int MyXactFlags ; 
 int /*<<< orphan*/  PostPrepare_Inval () ; 
 int /*<<< orphan*/  PostPrepare_Locks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostPrepare_MultiXact (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostPrepare_PgStat () ; 
 int /*<<< orphan*/  PostPrepare_PredicateLocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostPrepare_Twophase () ; 
 int /*<<< orphan*/  PostPrepare_smgr () ; 
 int /*<<< orphan*/  PreCommit_CheckForSerializationFailure () ; 
 int /*<<< orphan*/  PreCommit_Portals (int) ; 
 int /*<<< orphan*/  PreCommit_on_commit_actions () ; 
 int /*<<< orphan*/  ProcArrayClearTransaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  ResourceOwnerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 int /*<<< orphan*/  StartPrepare (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANS_DEFAULT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 scalar_t__ TRANS_PREPARE ; 
 int /*<<< orphan*/ * TopTransactionResourceOwner ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XACT_EVENT_PREPARE ; 
 int /*<<< orphan*/  XACT_EVENT_PRE_PREPARE ; 
 int XACT_FLAGS_ACCESSEDTEMPNAMESPACE ; 
 scalar_t__ XactHasExportedSnapshots () ; 
 scalar_t__ XactLastRecEnd ; 
 scalar_t__ XactManipulatesLogicalReplicationWorkers () ; 
 void* XactTopFullTransactionId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ nParallelCurrentXids ; 
 int /*<<< orphan*/  pgstat_report_xact_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * prepareGID ; 

__attribute__((used)) static void
PrepareTransaction(void)
{
	TransactionState s = CurrentTransactionState;
	TransactionId xid = GetCurrentTransactionId();
	GlobalTransaction gxact;
	TimestampTz prepared_at;

	Assert(!IsInParallelMode());

	ShowTransactionState("PrepareTransaction");

	/*
	 * check the current transaction state
	 */
	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "PrepareTransaction while in %s state",
			 TransStateAsString(s->state));
	Assert(s->parent == NULL);

	/*
	 * Do pre-commit processing that involves calling user-defined code, such
	 * as triggers.  Since closing cursors could queue trigger actions,
	 * triggers could open cursors, etc, we have to keep looping until there's
	 * nothing left to do.
	 */
	for (;;)
	{
		/*
		 * Fire all currently pending deferred triggers.
		 */
		AfterTriggerFireDeferred();

		/*
		 * Close open portals (converting holdable ones into static portals).
		 * If there weren't any, we are done ... otherwise loop back to check
		 * if they queued deferred triggers.  Lather, rinse, repeat.
		 */
		if (!PreCommit_Portals(true))
			break;
	}

	CallXactCallbacks(XACT_EVENT_PRE_PREPARE);

	/*
	 * The remaining actions cannot call any user-defined code, so it's safe
	 * to start shutting down within-transaction services.  But note that most
	 * of this stuff could still throw an error, which would switch us into
	 * the transaction-abort path.
	 */

	/* Shut down the deferred-trigger manager */
	AfterTriggerEndXact(true);

	/*
	 * Let ON COMMIT management do its thing (must happen after closing
	 * cursors, to avoid dangling-reference problems)
	 */
	PreCommit_on_commit_actions();

	/* close large objects before lower-level cleanup */
	AtEOXact_LargeObject(true);

	/*
	 * Mark serializable transaction as complete for predicate locking
	 * purposes.  This should be done as late as we can put it and still allow
	 * errors to be raised for failure patterns found at commit.
	 */
	PreCommit_CheckForSerializationFailure();

	/* NOTIFY will be handled below */

	/*
	 * Don't allow PREPARE TRANSACTION if we've accessed a temporary table in
	 * this transaction.  Having the prepared xact hold locks on another
	 * backend's temp table seems a bad idea --- for instance it would prevent
	 * the backend from exiting.  There are other problems too, such as how to
	 * clean up the source backend's local buffers and ON COMMIT state if the
	 * prepared xact includes a DROP of a temp table.
	 *
	 * Other objects types, like functions, operators or extensions, share the
	 * same restriction as they should not be created, locked or dropped as
	 * this can mess up with this session or even a follow-up session trying
	 * to use the same temporary namespace.
	 *
	 * We must check this after executing any ON COMMIT actions, because they
	 * might still access a temp relation.
	 *
	 * XXX In principle this could be relaxed to allow some useful special
	 * cases, such as a temp table created and dropped all within the
	 * transaction.  That seems to require much more bookkeeping though.
	 */
	if ((MyXactFlags & XACT_FLAGS_ACCESSEDTEMPNAMESPACE))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot PREPARE a transaction that has operated on temporary objects")));

	/*
	 * Likewise, don't allow PREPARE after pg_export_snapshot.  This could be
	 * supported if we added cleanup logic to twophase.c, but for now it
	 * doesn't seem worth the trouble.
	 */
	if (XactHasExportedSnapshots())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot PREPARE a transaction that has exported snapshots")));

	/*
	 * Don't allow PREPARE but for transaction that has/might kill logical
	 * replication workers.
	 */
	if (XactManipulatesLogicalReplicationWorkers())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot PREPARE a transaction that has manipulated logical replication workers")));

	/* Prevent cancel/die interrupt while cleaning up */
	HOLD_INTERRUPTS();

	/*
	 * set the current transaction state information appropriately during
	 * prepare processing
	 */
	s->state = TRANS_PREPARE;

	prepared_at = GetCurrentTimestamp();

	/* Tell bufmgr and smgr to prepare for commit */
	BufmgrCommit();

	/*
	 * Reserve the GID for this transaction. This could fail if the requested
	 * GID is invalid or already in use.
	 */
	gxact = MarkAsPreparing(xid, prepareGID, prepared_at,
							GetUserId(), MyDatabaseId);
	prepareGID = NULL;

	/*
	 * Collect data for the 2PC state file.  Note that in general, no actual
	 * state change should happen in the called modules during this step,
	 * since it's still possible to fail before commit, and in that case we
	 * want transaction abort to be able to clean up.  (In particular, the
	 * AtPrepare routines may error out if they find cases they cannot
	 * handle.)  State cleanup should happen in the PostPrepare routines
	 * below.  However, some modules can go ahead and clear state here because
	 * they wouldn't do anything with it during abort anyway.
	 *
	 * Note: because the 2PC state file records will be replayed in the same
	 * order they are made, the order of these calls has to match the order in
	 * which we want things to happen during COMMIT PREPARED or ROLLBACK
	 * PREPARED; in particular, pay attention to whether things should happen
	 * before or after releasing the transaction's locks.
	 */
	StartPrepare(gxact);

	AtPrepare_Notify();
	AtPrepare_Locks();
	AtPrepare_PredicateLocks();
	AtPrepare_PgStat();
	AtPrepare_MultiXact();
	AtPrepare_RelationMap();

	/*
	 * Here is where we really truly prepare.
	 *
	 * We have to record transaction prepares even if we didn't make any
	 * updates, because the transaction manager might get confused if we lose
	 * a global transaction.
	 */
	EndPrepare(gxact);

	/*
	 * Now we clean up backend-internal state and release internal resources.
	 */

	/* Reset XactLastRecEnd until the next transaction writes something */
	XactLastRecEnd = 0;

	/*
	 * Let others know about no transaction in progress by me.  This has to be
	 * done *after* the prepared transaction has been marked valid, else
	 * someone may think it is unlocked and recyclable.
	 */
	ProcArrayClearTransaction(MyProc);

	/*
	 * In normal commit-processing, this is all non-critical post-transaction
	 * cleanup.  When the transaction is prepared, however, it's important
	 * that the locks and other per-backend resources are transferred to the
	 * prepared transaction's PGPROC entry.  Note that if an error is raised
	 * here, it's too late to abort the transaction. XXX: This probably should
	 * be in a critical section, to force a PANIC if any of this fails, but
	 * that cure could be worse than the disease.
	 */

	CallXactCallbacks(XACT_EVENT_PREPARE);

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_BEFORE_LOCKS,
						 true, true);

	/* Check we've released all buffer pins */
	AtEOXact_Buffers(true);

	/* Clean up the relation cache */
	AtEOXact_RelationCache(true);

	/* notify doesn't need a postprepare call */

	PostPrepare_PgStat();

	PostPrepare_Inval();

	PostPrepare_smgr();

	PostPrepare_MultiXact(xid);

	PostPrepare_Locks(xid);
	PostPrepare_PredicateLocks(xid);

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_LOCKS,
						 true, true);
	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_AFTER_LOCKS,
						 true, true);

	/*
	 * Allow another backend to finish the transaction.  After
	 * PostPrepare_Twophase(), the transaction is completely detached from our
	 * backend.  The rest is just non-critical cleanup of backend-local state.
	 */
	PostPrepare_Twophase();

	/* PREPARE acts the same as COMMIT as far as GUC is concerned */
	AtEOXact_GUC(true, 1);
	AtEOXact_SPI(true);
	AtEOXact_Enum();
	AtEOXact_on_commit_actions(true);
	AtEOXact_Namespace(true, false);
	AtEOXact_SMgr();
	AtEOXact_Files(true);
	AtEOXact_ComboCid();
	AtEOXact_HashTables(true);
	/* don't call AtEOXact_PgStat here; we fixed pgstat state above */
	AtEOXact_Snapshot(true, true);
	pgstat_report_xact_timestamp(0);

	CurrentResourceOwner = NULL;
	ResourceOwnerDelete(TopTransactionResourceOwner);
	s->curTransactionOwner = NULL;
	CurTransactionResourceOwner = NULL;
	TopTransactionResourceOwner = NULL;

	AtCommit_Memory();

	s->fullTransactionId = InvalidFullTransactionId;
	s->subTransactionId = InvalidSubTransactionId;
	s->nestingLevel = 0;
	s->gucNestLevel = 0;
	s->childXids = NULL;
	s->nChildXids = 0;
	s->maxChildXids = 0;

	XactTopFullTransactionId = InvalidFullTransactionId;
	nParallelCurrentXids = 0;

	/*
	 * done with 1st phase commit processing, set current transaction state
	 * back to default
	 */
	s->state = TRANS_DEFAULT;

	RESUME_INTERRUPTS();
}