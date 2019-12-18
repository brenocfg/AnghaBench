#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ftrace_graph_ent {unsigned long func; scalar_t__ depth; } ;
struct TYPE_2__ {scalar_t__ curr_ret_depth; int /*<<< orphan*/  curr_ret_stack; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ftrace_graph_entry (struct ftrace_graph_ent*) ; 
 scalar_t__ ftrace_push_return_trace (unsigned long,unsigned long,unsigned long,unsigned long*) ; 

int function_graph_enter(unsigned long ret, unsigned long func,
			 unsigned long frame_pointer, unsigned long *retp)
{
	struct ftrace_graph_ent trace;

	trace.func = func;
	trace.depth = ++current->curr_ret_depth;

	if (ftrace_push_return_trace(ret, func, frame_pointer, retp))
		goto out;

	/* Only trace if the calling function expects to */
	if (!ftrace_graph_entry(&trace))
		goto out_ret;

	return 0;
 out_ret:
	current->curr_ret_stack--;
 out:
	current->curr_ret_depth--;
	return -EBUSY;
}