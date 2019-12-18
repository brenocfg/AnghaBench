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
struct TYPE_7__ {scalar_t__ calldepth; TYPE_1__* argstack; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ PLySavedArgs ;
typedef  TYPE_2__ PLyProcedure ;

/* Variables and functions */
 TYPE_1__* PLy_function_save_args (TYPE_2__*) ; 

__attribute__((used)) static void
PLy_global_args_push(PLyProcedure *proc)
{
	/* We only need to push if we are already inside some active call */
	if (proc->calldepth > 0)
	{
		PLySavedArgs *node;

		/* Build a struct containing current argument values */
		node = PLy_function_save_args(proc);

		/*
		 * Push the saved argument values into the procedure's stack.  Once we
		 * modify either proc->argstack or proc->calldepth, we had better
		 * return without the possibility of error.
		 */
		node->next = proc->argstack;
		proc->argstack = node;
	}
	proc->calldepth++;
}