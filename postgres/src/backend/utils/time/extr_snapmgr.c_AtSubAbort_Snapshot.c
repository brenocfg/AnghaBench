#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int active_count; scalar_t__ regd_count; } ;
struct TYPE_5__ {int as_level; TYPE_3__* as_snap; struct TYPE_5__* as_next; } ;
typedef  TYPE_1__ ActiveSnapshotElt ;

/* Variables and functions */
 TYPE_1__* ActiveSnapshot ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FreeSnapshot (TYPE_3__*) ; 
 int /*<<< orphan*/ * OldestActiveSnapshot ; 
 int /*<<< orphan*/  SnapshotResetXmin () ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
AtSubAbort_Snapshot(int level)
{
	/* Forget the active snapshots set by this subtransaction */
	while (ActiveSnapshot && ActiveSnapshot->as_level >= level)
	{
		ActiveSnapshotElt *next;

		next = ActiveSnapshot->as_next;

		/*
		 * Decrement the snapshot's active count.  If it's still registered or
		 * marked as active by an outer subtransaction, we can't free it yet.
		 */
		Assert(ActiveSnapshot->as_snap->active_count >= 1);
		ActiveSnapshot->as_snap->active_count -= 1;

		if (ActiveSnapshot->as_snap->active_count == 0 &&
			ActiveSnapshot->as_snap->regd_count == 0)
			FreeSnapshot(ActiveSnapshot->as_snap);

		/* and free the stack element */
		pfree(ActiveSnapshot);

		ActiveSnapshot = next;
		if (ActiveSnapshot == NULL)
			OldestActiveSnapshot = NULL;
	}

	SnapshotResetXmin();
}