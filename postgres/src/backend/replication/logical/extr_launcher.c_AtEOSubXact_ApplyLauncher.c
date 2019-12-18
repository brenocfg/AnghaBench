#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nestDepth; int /*<<< orphan*/  workers; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ StopWorkersData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ ) ; 
 TYPE_1__* on_commit_stop_workers ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
AtEOSubXact_ApplyLauncher(bool isCommit, int nestDepth)
{
	StopWorkersData *parent;

	/* Exit immediately if there's no work to do at this level. */
	if (on_commit_stop_workers == NULL ||
		on_commit_stop_workers->nestDepth < nestDepth)
		return;

	Assert(on_commit_stop_workers->nestDepth == nestDepth);

	parent = on_commit_stop_workers->parent;

	if (isCommit)
	{
		/*
		 * If the upper stack element is not an immediate parent
		 * subtransaction, just decrement the notional nesting depth without
		 * doing any real work.  Else, we need to merge the current workers
		 * list into the parent.
		 */
		if (!parent || parent->nestDepth < nestDepth - 1)
		{
			on_commit_stop_workers->nestDepth--;
			return;
		}

		parent->workers =
			list_concat(parent->workers, on_commit_stop_workers->workers);
	}
	else
	{
		/*
		 * Abandon everything that was done at this nesting level.  Explicitly
		 * free memory to avoid a transaction-lifespan leak.
		 */
		list_free_deep(on_commit_stop_workers->workers);
	}

	/*
	 * We have taken care of the current subtransaction workers list for both
	 * abort or commit. So we are ready to pop the stack.
	 */
	pfree(on_commit_stop_workers);
	on_commit_stop_workers = parent;
}