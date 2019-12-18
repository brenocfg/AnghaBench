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
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/ * curTransactionOwner; TYPE_1__* parent; int /*<<< orphan*/  prevXactReadOnly; int /*<<< orphan*/  nestingLevel; int /*<<< orphan*/  subTransactionId; int /*<<< orphan*/  gucNestLevel; int /*<<< orphan*/  fullTransactionId; scalar_t__ parallelModeLevel; } ;
struct TYPE_4__ {int /*<<< orphan*/ * curTransactionOwner; int /*<<< orphan*/  subTransactionId; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  AtSubCommit_Memory () ; 
 int /*<<< orphan*/  AtSubCommit_Notify () ; 
 int /*<<< orphan*/  AtSubCommit_Portals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AtSubCommit_Snapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtSubCommit_childXids () ; 
 int /*<<< orphan*/  AtSubCommit_smgr () ; 
 int /*<<< orphan*/  CallSubXactCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/ * CurTransactionResourceOwner ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 TYPE_2__* CurrentTransactionState ; 
 scalar_t__ FullTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  PopTransaction () ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  ResourceOwnerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SUBXACT_EVENT_COMMIT_SUB ; 
 int /*<<< orphan*/  SUBXACT_EVENT_PRE_COMMIT_SUB ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 scalar_t__ TRANS_COMMIT ; 
 scalar_t__ TRANS_DEFAULT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XactLockTableDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactReadOnly ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CommitSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	ShowTransactionState("CommitSubTransaction");

	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "CommitSubTransaction while in %s state",
			 TransStateAsString(s->state));

	/* Pre-commit processing goes here */

	CallSubXactCallbacks(SUBXACT_EVENT_PRE_COMMIT_SUB, s->subTransactionId,
						 s->parent->subTransactionId);

	/* If in parallel mode, clean up workers and exit parallel mode. */
	if (IsInParallelMode())
	{
		AtEOSubXact_Parallel(true, s->subTransactionId);
		s->parallelModeLevel = 0;
	}

	/* Do the actual "commit", such as it is */
	s->state = TRANS_COMMIT;

	/* Must CCI to ensure commands of subtransaction are seen as done */
	CommandCounterIncrement();

	/*
	 * Prior to 8.4 we marked subcommit in clog at this point.  We now only
	 * perform that step, if required, as part of the atomic update of the
	 * whole transaction tree at top level commit or abort.
	 */

	/* Post-commit cleanup */
	if (FullTransactionIdIsValid(s->fullTransactionId))
		AtSubCommit_childXids();
	AfterTriggerEndSubXact(true);
	AtSubCommit_Portals(s->subTransactionId,
						s->parent->subTransactionId,
						s->parent->curTransactionOwner);
	AtEOSubXact_LargeObject(true, s->subTransactionId,
							s->parent->subTransactionId);
	AtSubCommit_Notify();

	CallSubXactCallbacks(SUBXACT_EVENT_COMMIT_SUB, s->subTransactionId,
						 s->parent->subTransactionId);

	ResourceOwnerRelease(s->curTransactionOwner,
						 RESOURCE_RELEASE_BEFORE_LOCKS,
						 true, false);
	AtEOSubXact_RelationCache(true, s->subTransactionId,
							  s->parent->subTransactionId);
	AtEOSubXact_Inval(true);
	AtSubCommit_smgr();

	/*
	 * The only lock we actually release here is the subtransaction XID lock.
	 */
	CurrentResourceOwner = s->curTransactionOwner;
	if (FullTransactionIdIsValid(s->fullTransactionId))
		XactLockTableDelete(XidFromFullTransactionId(s->fullTransactionId));

	/*
	 * Other locks should get transferred to their parent resource owner.
	 */
	ResourceOwnerRelease(s->curTransactionOwner,
						 RESOURCE_RELEASE_LOCKS,
						 true, false);
	ResourceOwnerRelease(s->curTransactionOwner,
						 RESOURCE_RELEASE_AFTER_LOCKS,
						 true, false);

	AtEOXact_GUC(true, s->gucNestLevel);
	AtEOSubXact_SPI(true, s->subTransactionId);
	AtEOSubXact_on_commit_actions(true, s->subTransactionId,
								  s->parent->subTransactionId);
	AtEOSubXact_Namespace(true, s->subTransactionId,
						  s->parent->subTransactionId);
	AtEOSubXact_Files(true, s->subTransactionId,
					  s->parent->subTransactionId);
	AtEOSubXact_HashTables(true, s->nestingLevel);
	AtEOSubXact_PgStat(true, s->nestingLevel);
	AtSubCommit_Snapshot(s->nestingLevel);
	AtEOSubXact_ApplyLauncher(true, s->nestingLevel);

	/*
	 * We need to restore the upper transaction's read-only state, in case the
	 * upper is read-write while the child is read-only; GUC will incorrectly
	 * think it should leave the child state in place.
	 */
	XactReadOnly = s->prevXactReadOnly;

	CurrentResourceOwner = s->parent->curTransactionOwner;
	CurTransactionResourceOwner = s->parent->curTransactionOwner;
	ResourceOwnerDelete(s->curTransactionOwner);
	s->curTransactionOwner = NULL;

	AtSubCommit_Memory();

	s->state = TRANS_DEFAULT;

	PopTransaction();
}