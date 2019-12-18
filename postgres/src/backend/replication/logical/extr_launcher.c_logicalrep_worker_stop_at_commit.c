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
struct TYPE_6__ {void* relid; void* subid; } ;
struct TYPE_5__ {int nestDepth; int /*<<< orphan*/  workers; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ StopWorkersData ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ LogicalRepWorkerId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GetCurrentTransactionNestLevel () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* on_commit_stop_workers ; 
 void* palloc (int) ; 

void
logicalrep_worker_stop_at_commit(Oid subid, Oid relid)
{
	int			nestDepth = GetCurrentTransactionNestLevel();
	LogicalRepWorkerId *wid;
	MemoryContext oldctx;

	/* Make sure we store the info in context that survives until commit. */
	oldctx = MemoryContextSwitchTo(TopTransactionContext);

	/* Check that previous transactions were properly cleaned up. */
	Assert(on_commit_stop_workers == NULL ||
		   nestDepth >= on_commit_stop_workers->nestDepth);

	/*
	 * Push a new stack element if we don't already have one for the current
	 * nestDepth.
	 */
	if (on_commit_stop_workers == NULL ||
		nestDepth > on_commit_stop_workers->nestDepth)
	{
		StopWorkersData *newdata = palloc(sizeof(StopWorkersData));

		newdata->nestDepth = nestDepth;
		newdata->workers = NIL;
		newdata->parent = on_commit_stop_workers;
		on_commit_stop_workers = newdata;
	}

	/*
	 * Finally add a new worker into the worker list of the current
	 * subtransaction.
	 */
	wid = palloc(sizeof(LogicalRepWorkerId));
	wid->subid = subid;
	wid->relid = relid;
	on_commit_stop_workers->workers =
		lappend(on_commit_stop_workers->workers, wid);

	MemoryContextSwitchTo(oldctx);
}