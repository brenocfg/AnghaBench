#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tailfree; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct TYPE_4__ {int query_depth; int /*<<< orphan*/ * state; scalar_t__ maxquerydepth; int /*<<< orphan*/ * query_stack; scalar_t__ maxtransdepth; int /*<<< orphan*/ * trans_stack; TYPE_1__ events; int /*<<< orphan*/ * event_cxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 TYPE_2__ afterTriggers ; 

void
AfterTriggerEndXact(bool isCommit)
{
	/*
	 * Forget the pending-events list.
	 *
	 * Since all the info is in TopTransactionContext or children thereof, we
	 * don't really need to do anything to reclaim memory.  However, the
	 * pending-events list could be large, and so it's useful to discard it as
	 * soon as possible --- especially if we are aborting because we ran out
	 * of memory for the list!
	 */
	if (afterTriggers.event_cxt)
	{
		MemoryContextDelete(afterTriggers.event_cxt);
		afterTriggers.event_cxt = NULL;
		afterTriggers.events.head = NULL;
		afterTriggers.events.tail = NULL;
		afterTriggers.events.tailfree = NULL;
	}

	/*
	 * Forget any subtransaction state as well.  Since this can't be very
	 * large, we let the eventual reset of TopTransactionContext free the
	 * memory instead of doing it here.
	 */
	afterTriggers.trans_stack = NULL;
	afterTriggers.maxtransdepth = 0;


	/*
	 * Forget the query stack and constraint-related state information.  As
	 * with the subtransaction state information, we don't bother freeing the
	 * memory here.
	 */
	afterTriggers.query_stack = NULL;
	afterTriggers.maxquerydepth = 0;
	afterTriggers.state = NULL;

	/* No more afterTriggers manipulation until next transaction starts. */
	afterTriggers.query_depth = -1;
}