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
struct TYPE_7__ {int calldepth; TYPE_1__* argstack; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ PLySavedArgs ;
typedef  TYPE_2__ PLyProcedure ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PLy_function_restore_args (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
PLy_global_args_pop(PLyProcedure *proc)
{
	Assert(proc->calldepth > 0);
	/* We only need to pop if we were already inside some active call */
	if (proc->calldepth > 1)
	{
		PLySavedArgs *ptr = proc->argstack;

		/* Pop the callstack */
		Assert(ptr != NULL);
		proc->argstack = ptr->next;
		proc->calldepth--;

		/* Restore argument values, then free ptr */
		PLy_function_restore_args(proc, ptr);
	}
	else
	{
		/* Exiting call depth 1 */
		Assert(proc->argstack == NULL);
		proc->calldepth--;

		/*
		 * We used to delete the named arguments (but not "args") from the
		 * proc's globals dict when exiting the outermost call level for a
		 * function.  This seems rather pointless though: nothing can see the
		 * dict until the function is called again, at which time we'll
		 * overwrite those dict entries.  So don't bother with that.
		 */
	}
}