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
typedef  int /*<<< orphan*/  WAIT_ORDER ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  EDGE ;
typedef  int /*<<< orphan*/  DEADLOCK_INFO ;

/* Variables and functions */
 int MaxBackends ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int* afterConstraints ; 
 int* beforeConstraints ; 
 int /*<<< orphan*/ * curConstraints ; 
 int /*<<< orphan*/ * deadlockDetails ; 
 int maxCurConstraints ; 
 int maxPossibleConstraints ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * possibleConstraints ; 
 int /*<<< orphan*/ ** topoProcs ; 
 int /*<<< orphan*/ ** visitedProcs ; 
 int /*<<< orphan*/ ** waitOrderProcs ; 
 int /*<<< orphan*/ * waitOrders ; 

void
InitDeadLockChecking(void)
{
	MemoryContext oldcxt;

	/* Make sure allocations are permanent */
	oldcxt = MemoryContextSwitchTo(TopMemoryContext);

	/*
	 * FindLockCycle needs at most MaxBackends entries in visitedProcs[] and
	 * deadlockDetails[].
	 */
	visitedProcs = (PGPROC **) palloc(MaxBackends * sizeof(PGPROC *));
	deadlockDetails = (DEADLOCK_INFO *) palloc(MaxBackends * sizeof(DEADLOCK_INFO));

	/*
	 * TopoSort needs to consider at most MaxBackends wait-queue entries, and
	 * it needn't run concurrently with FindLockCycle.
	 */
	topoProcs = visitedProcs;	/* re-use this space */
	beforeConstraints = (int *) palloc(MaxBackends * sizeof(int));
	afterConstraints = (int *) palloc(MaxBackends * sizeof(int));

	/*
	 * We need to consider rearranging at most MaxBackends/2 wait queues
	 * (since it takes at least two waiters in a queue to create a soft edge),
	 * and the expanded form of the wait queues can't involve more than
	 * MaxBackends total waiters.
	 */
	waitOrders = (WAIT_ORDER *)
		palloc((MaxBackends / 2) * sizeof(WAIT_ORDER));
	waitOrderProcs = (PGPROC **) palloc(MaxBackends * sizeof(PGPROC *));

	/*
	 * Allow at most MaxBackends distinct constraints in a configuration. (Is
	 * this enough?  In practice it seems it should be, but I don't quite see
	 * how to prove it.  If we run out, we might fail to find a workable wait
	 * queue rearrangement even though one exists.)  NOTE that this number
	 * limits the maximum recursion depth of DeadLockCheckRecurse. Making it
	 * really big might potentially allow a stack-overflow problem.
	 */
	maxCurConstraints = MaxBackends;
	curConstraints = (EDGE *) palloc(maxCurConstraints * sizeof(EDGE));

	/*
	 * Allow up to 3*MaxBackends constraints to be saved without having to
	 * re-run TestConfiguration.  (This is probably more than enough, but we
	 * can survive if we run low on space by doing excess runs of
	 * TestConfiguration to re-compute constraint lists each time needed.) The
	 * last MaxBackends entries in possibleConstraints[] are reserved as
	 * output workspace for FindLockCycle.
	 */
	maxPossibleConstraints = MaxBackends * 4;
	possibleConstraints =
		(EDGE *) palloc(maxPossibleConstraints * sizeof(EDGE));

	MemoryContextSwitchTo(oldcxt);
}