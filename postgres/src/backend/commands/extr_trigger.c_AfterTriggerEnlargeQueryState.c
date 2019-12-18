#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int maxquerydepth; int query_depth; TYPE_2__* query_stack; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tailfree; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct TYPE_6__ {int /*<<< orphan*/  tables; int /*<<< orphan*/ * fdw_tuplestore; TYPE_1__ events; } ;
typedef  TYPE_2__ AfterTriggersQueryData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int Max (int,int) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 TYPE_4__ afterTriggers ; 
 scalar_t__ repalloc (TYPE_2__*,int) ; 

__attribute__((used)) static void
AfterTriggerEnlargeQueryState(void)
{
	int			init_depth = afterTriggers.maxquerydepth;

	Assert(afterTriggers.query_depth >= afterTriggers.maxquerydepth);

	if (afterTriggers.maxquerydepth == 0)
	{
		int			new_alloc = Max(afterTriggers.query_depth + 1, 8);

		afterTriggers.query_stack = (AfterTriggersQueryData *)
			MemoryContextAlloc(TopTransactionContext,
							   new_alloc * sizeof(AfterTriggersQueryData));
		afterTriggers.maxquerydepth = new_alloc;
	}
	else
	{
		/* repalloc will keep the stack in the same context */
		int			old_alloc = afterTriggers.maxquerydepth;
		int			new_alloc = Max(afterTriggers.query_depth + 1,
									old_alloc * 2);

		afterTriggers.query_stack = (AfterTriggersQueryData *)
			repalloc(afterTriggers.query_stack,
					 new_alloc * sizeof(AfterTriggersQueryData));
		afterTriggers.maxquerydepth = new_alloc;
	}

	/* Initialize new array entries to empty */
	while (init_depth < afterTriggers.maxquerydepth)
	{
		AfterTriggersQueryData *qs = &afterTriggers.query_stack[init_depth];

		qs->events.head = NULL;
		qs->events.tail = NULL;
		qs->events.tailfree = NULL;
		qs->fdw_tuplestore = NULL;
		qs->tables = NIL;

		++init_depth;
	}
}