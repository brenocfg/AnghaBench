#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maxtransdepth; int /*<<< orphan*/  firing_counter; TYPE_1__* trans_stack; int /*<<< orphan*/  query_depth; int /*<<< orphan*/  events; } ;
struct TYPE_4__ {int /*<<< orphan*/  firing_counter; int /*<<< orphan*/  query_depth; int /*<<< orphan*/  events; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ AfterTriggersTransData ;

/* Variables and functions */
 int GetCurrentTransactionNestLevel () ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 TYPE_3__ afterTriggers ; 
 scalar_t__ repalloc (TYPE_1__*,int) ; 

void
AfterTriggerBeginSubXact(void)
{
	int			my_level = GetCurrentTransactionNestLevel();

	/*
	 * Allocate more space in the trans_stack if needed.  (Note: because the
	 * minimum nest level of a subtransaction is 2, we waste the first couple
	 * entries of the array; not worth the notational effort to avoid it.)
	 */
	while (my_level >= afterTriggers.maxtransdepth)
	{
		if (afterTriggers.maxtransdepth == 0)
		{
			/* Arbitrarily initialize for max of 8 subtransaction levels */
			afterTriggers.trans_stack = (AfterTriggersTransData *)
				MemoryContextAlloc(TopTransactionContext,
								   8 * sizeof(AfterTriggersTransData));
			afterTriggers.maxtransdepth = 8;
		}
		else
		{
			/* repalloc will keep the stack in the same context */
			int			new_alloc = afterTriggers.maxtransdepth * 2;

			afterTriggers.trans_stack = (AfterTriggersTransData *)
				repalloc(afterTriggers.trans_stack,
						 new_alloc * sizeof(AfterTriggersTransData));
			afterTriggers.maxtransdepth = new_alloc;
		}
	}

	/*
	 * Push the current information into the stack.  The SET CONSTRAINTS state
	 * is not saved until/unless changed.  Likewise, we don't make a
	 * per-subtransaction event context until needed.
	 */
	afterTriggers.trans_stack[my_level].state = NULL;
	afterTriggers.trans_stack[my_level].events = afterTriggers.events;
	afterTriggers.trans_stack[my_level].query_depth = afterTriggers.query_depth;
	afterTriggers.trans_stack[my_level].firing_counter = afterTriggers.firing_counter;
}