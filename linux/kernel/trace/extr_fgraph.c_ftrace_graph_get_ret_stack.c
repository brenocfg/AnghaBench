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
struct task_struct {int curr_ret_stack; struct ftrace_ret_stack* ret_stack; } ;
struct ftrace_ret_stack {int dummy; } ;

/* Variables and functions */

struct ftrace_ret_stack *
ftrace_graph_get_ret_stack(struct task_struct *task, int idx)
{
	idx = task->curr_ret_stack - idx;

	if (idx >= 0 && idx <= task->curr_ret_stack)
		return &task->ret_stack[idx];

	return NULL;
}