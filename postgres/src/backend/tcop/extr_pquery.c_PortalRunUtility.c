#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * utilityStmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  portalContext; int /*<<< orphan*/  queryEnv; int /*<<< orphan*/  portalParams; int /*<<< orphan*/  sourceText; int /*<<< orphan*/ * holdSnapshot; } ;
typedef  int /*<<< orphan*/ * Snapshot ;
typedef  TYPE_1__* Portal ;
typedef  TYPE_2__ PlannedStmt ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 scalar_t__ ActiveSnapshotSet () ; 
 int /*<<< orphan*/  CheckPointStmt ; 
 int /*<<< orphan*/  ConstraintsSetStmt ; 
 int /*<<< orphan*/  FetchStmt ; 
 int /*<<< orphan*/ * GetActiveSnapshot () ; 
 int /*<<< orphan*/ * GetTransactionSnapshot () ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListenStmt ; 
 int /*<<< orphan*/  LockStmt ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotifyStmt ; 
 int /*<<< orphan*/  PROCESS_UTILITY_QUERY ; 
 int /*<<< orphan*/  PROCESS_UTILITY_TOPLEVEL ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  ProcessUtility (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RegisterSnapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionStmt ; 
 int /*<<< orphan*/  UnlistenStmt ; 
 int /*<<< orphan*/  VariableSetStmt ; 
 int /*<<< orphan*/  VariableShowStmt ; 

__attribute__((used)) static void
PortalRunUtility(Portal portal, PlannedStmt *pstmt,
				 bool isTopLevel, bool setHoldSnapshot,
				 DestReceiver *dest, char *completionTag)
{
	Node	   *utilityStmt = pstmt->utilityStmt;
	Snapshot	snapshot;

	/*
	 * Set snapshot if utility stmt needs one.  Most reliable way to do this
	 * seems to be to enumerate those that do not need one; this is a short
	 * list.  Transaction control, LOCK, and SET must *not* set a snapshot
	 * since they need to be executable at the start of a transaction-snapshot
	 * mode transaction without freezing a snapshot.  By extension we allow
	 * SHOW not to set a snapshot.  The other stmts listed are just efficiency
	 * hacks.  Beware of listing anything that can modify the database --- if,
	 * say, it has to update an index with expressions that invoke
	 * user-defined functions, then it had better have a snapshot.
	 */
	if (!(IsA(utilityStmt, TransactionStmt) ||
		  IsA(utilityStmt, LockStmt) ||
		  IsA(utilityStmt, VariableSetStmt) ||
		  IsA(utilityStmt, VariableShowStmt) ||
		  IsA(utilityStmt, ConstraintsSetStmt) ||
	/* efficiency hacks from here down */
		  IsA(utilityStmt, FetchStmt) ||
		  IsA(utilityStmt, ListenStmt) ||
		  IsA(utilityStmt, NotifyStmt) ||
		  IsA(utilityStmt, UnlistenStmt) ||
		  IsA(utilityStmt, CheckPointStmt)))
	{
		snapshot = GetTransactionSnapshot();
		/* If told to, register the snapshot we're using and save in portal */
		if (setHoldSnapshot)
		{
			snapshot = RegisterSnapshot(snapshot);
			portal->holdSnapshot = snapshot;
		}
		PushActiveSnapshot(snapshot);
		/* PushActiveSnapshot might have copied the snapshot */
		snapshot = GetActiveSnapshot();
	}
	else
		snapshot = NULL;

	ProcessUtility(pstmt,
				   portal->sourceText,
				   isTopLevel ? PROCESS_UTILITY_TOPLEVEL : PROCESS_UTILITY_QUERY,
				   portal->portalParams,
				   portal->queryEnv,
				   dest,
				   completionTag);

	/* Some utility statements may change context on us */
	MemoryContextSwitchTo(portal->portalContext);

	/*
	 * Some utility commands may pop the ActiveSnapshot stack from under us,
	 * so be careful to only pop the stack if our snapshot is still at the
	 * top.
	 */
	if (snapshot != NULL && ActiveSnapshotSet() &&
		snapshot == GetActiveSnapshot())
		PopActiveSnapshot();
}