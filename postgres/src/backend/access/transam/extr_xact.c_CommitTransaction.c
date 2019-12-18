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
struct TYPE_5__ {scalar_t__ blockState; scalar_t__ state; scalar_t__ maxChildXids; scalar_t__ nChildXids; int /*<<< orphan*/ * childXids; scalar_t__ gucNestLevel; scalar_t__ nestingLevel; int /*<<< orphan*/  subTransactionId; void* fullTransactionId; int /*<<< orphan*/ * curTransactionOwner; scalar_t__ parallelModeLevel; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerEndXact (int) ; 
 int /*<<< orphan*/  AfterTriggerFireDeferred () ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtCommit_Memory () ; 
 int /*<<< orphan*/  AtCommit_Notify () ; 
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
 int /*<<< orphan*/  AtEOXact_Snapshot (int,int) ; 
 int /*<<< orphan*/  AtEOXact_on_commit_actions (int) ; 
 int /*<<< orphan*/  CallXactCallbacks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurTransactionResourceOwner ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  EnterParallelMode () ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 void* InvalidFullTransactionId ; 
 int /*<<< orphan*/  InvalidSubTransactionId ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsInParallelMode () ; 
 TYPE_2__* MyProc ; 
 int /*<<< orphan*/  ParallelWorkerReportLastRecEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PreCommit_CheckForSerializationFailure () ; 
 int /*<<< orphan*/  PreCommit_Notify () ; 
 int /*<<< orphan*/  PreCommit_Portals (int) ; 
 int /*<<< orphan*/  PreCommit_on_commit_actions () ; 
 int /*<<< orphan*/  ProcArrayEndTransaction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  RecordTransactionCommit () ; 
 int /*<<< orphan*/  ResourceOwnerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 scalar_t__ TBLOCK_PARALLEL_INPROGRESS ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_TRANSACTION_COMMIT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANS_COMMIT ; 
 scalar_t__ TRANS_DEFAULT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 int /*<<< orphan*/ * TopTransactionResourceOwner ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XACT_EVENT_COMMIT ; 
 int /*<<< orphan*/  XACT_EVENT_PARALLEL_COMMIT ; 
 int /*<<< orphan*/  XACT_EVENT_PARALLEL_PRE_COMMIT ; 
 int /*<<< orphan*/  XACT_EVENT_PRE_COMMIT ; 
 int /*<<< orphan*/  XactLastRecEnd ; 
 void* XactTopFullTransactionId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nParallelCurrentXids ; 
 int /*<<< orphan*/  pgstat_report_xact_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrDoPendingDeletes (int) ; 

__attribute__((used)) static void
CommitTransaction(void)
{
	TransactionState s = CurrentTransactionState;
	TransactionId latestXid;
	bool		is_parallel_worker;

	is_parallel_worker = (s->blockState == TBLOCK_PARALLEL_INPROGRESS);

	/* Enforce parallel mode restrictions during parallel worker commit. */
	if (is_parallel_worker)
		EnterParallelMode();

	ShowTransactionState("CommitTransaction");

	/*
	 * check the current transaction state
	 */
	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "CommitTransaction while in %s state",
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
		if (!PreCommit_Portals(false))
			break;
	}

	CallXactCallbacks(is_parallel_worker ? XACT_EVENT_PARALLEL_PRE_COMMIT
					  : XACT_EVENT_PRE_COMMIT);

	/*
	 * The remaining actions cannot call any user-defined code, so it's safe
	 * to start shutting down within-transaction services.  But note that most
	 * of this stuff could still throw an error, which would switch us into
	 * the transaction-abort path.
	 */

	/* If we might have parallel workers, clean them up now. */
	if (IsInParallelMode())
		AtEOXact_Parallel(true);

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
	 * errors to be raised for failure patterns found at commit.  This is not
	 * appropriate in a parallel worker however, because we aren't committing
	 * the leader's transaction and its serializable state will live on.
	 */
	if (!is_parallel_worker)
		PreCommit_CheckForSerializationFailure();

	/*
	 * Insert notifications sent by NOTIFY commands into the queue.  This
	 * should be late in the pre-commit sequence to minimize time spent
	 * holding the notify-insertion lock.
	 */
	PreCommit_Notify();

	/* Prevent cancel/die interrupt while cleaning up */
	HOLD_INTERRUPTS();

	/* Commit updates to the relation map --- do this as late as possible */
	AtEOXact_RelationMap(true, is_parallel_worker);

	/*
	 * set the current transaction state information appropriately during
	 * commit processing
	 */
	s->state = TRANS_COMMIT;
	s->parallelModeLevel = 0;

	if (!is_parallel_worker)
	{
		/*
		 * We need to mark our XIDs as committed in pg_xact.  This is where we
		 * durably commit.
		 */
		latestXid = RecordTransactionCommit();
	}
	else
	{
		/*
		 * We must not mark our XID committed; the parallel master is
		 * responsible for that.
		 */
		latestXid = InvalidTransactionId;

		/*
		 * Make sure the master will know about any WAL we wrote before it
		 * commits.
		 */
		ParallelWorkerReportLastRecEnd(XactLastRecEnd);
	}

	TRACE_POSTGRESQL_TRANSACTION_COMMIT(MyProc->lxid);

	/*
	 * Let others know about no transaction in progress by me. Note that this
	 * must be done _before_ releasing locks we hold and _after_
	 * RecordTransactionCommit.
	 */
	ProcArrayEndTransaction(MyProc, latestXid);

	/*
	 * This is all post-commit cleanup.  Note that if an error is raised here,
	 * it's too late to abort the transaction.  This should be just
	 * noncritical resource releasing.
	 *
	 * The ordering of operations is not entirely random.  The idea is:
	 * release resources visible to other backends (eg, files, buffer pins);
	 * then release locks; then release backend-local resources. We want to
	 * release locks at the point where any backend waiting for us will see
	 * our transaction as being fully cleaned up.
	 *
	 * Resources that can be associated with individual queries are handled by
	 * the ResourceOwner mechanism.  The other calls here are for backend-wide
	 * state.
	 */

	CallXactCallbacks(is_parallel_worker ? XACT_EVENT_PARALLEL_COMMIT
					  : XACT_EVENT_COMMIT);

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_BEFORE_LOCKS,
						 true, true);

	/* Check we've released all buffer pins */
	AtEOXact_Buffers(true);

	/* Clean up the relation cache */
	AtEOXact_RelationCache(true);

	/*
	 * Make catalog changes visible to all backends.  This has to happen after
	 * relcache references are dropped (see comments for
	 * AtEOXact_RelationCache), but before locks are released (if anyone is
	 * waiting for lock on a relation we've modified, we want them to know
	 * about the catalog change before they start using the relation).
	 */
	AtEOXact_Inval(true);

	AtEOXact_MultiXact();

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_LOCKS,
						 true, true);
	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_AFTER_LOCKS,
						 true, true);

	/*
	 * Likewise, dropping of files deleted during the transaction is best done
	 * after releasing relcache and buffer pins.  (This is not strictly
	 * necessary during commit, since such pins should have been released
	 * already, but this ordering is definitely critical during abort.)  Since
	 * this may take many seconds, also delay until after releasing locks.
	 * Other backends will observe the attendant catalog changes and not
	 * attempt to access affected files.
	 */
	smgrDoPendingDeletes(true);

	AtCommit_Notify();
	AtEOXact_GUC(true, 1);
	AtEOXact_SPI(true);
	AtEOXact_Enum();
	AtEOXact_on_commit_actions(true);
	AtEOXact_Namespace(true, is_parallel_worker);
	AtEOXact_SMgr();
	AtEOXact_Files(true);
	AtEOXact_ComboCid();
	AtEOXact_HashTables(true);
	AtEOXact_PgStat(true, is_parallel_worker);
	AtEOXact_Snapshot(true, false);
	AtEOXact_ApplyLauncher(true);
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
	 * done with commit processing, set current transaction state back to
	 * default
	 */
	s->state = TRANS_DEFAULT;

	RESUME_INTERRUPTS();
}