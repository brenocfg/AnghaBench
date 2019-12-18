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
struct task_struct {int curr_ret_stack; int curr_ret_depth; int /*<<< orphan*/ * ret_stack; } ;
struct ftrace_ret_stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTRACE_RETFUNC_DEPTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ftrace_graph_active ; 
 int /*<<< orphan*/  graph_init_task (struct task_struct*,struct ftrace_ret_stack*) ; 
 struct ftrace_ret_stack* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ftrace_graph_init_task(struct task_struct *t)
{
	/* Make sure we do not use the parent ret_stack */
	t->ret_stack = NULL;
	t->curr_ret_stack = -1;
	t->curr_ret_depth = -1;

	if (ftrace_graph_active) {
		struct ftrace_ret_stack *ret_stack;

		ret_stack = kmalloc_array(FTRACE_RETFUNC_DEPTH,
					  sizeof(struct ftrace_ret_stack),
					  GFP_KERNEL);
		if (!ret_stack)
			return;
		graph_init_task(t, ret_stack);
	}
}