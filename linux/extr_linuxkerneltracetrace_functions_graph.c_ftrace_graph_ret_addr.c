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
struct task_struct {int curr_ret_stack; TYPE_1__* ret_stack; } ;
struct TYPE_2__ {unsigned long ret; } ;

/* Variables and functions */
 scalar_t__ return_to_handler ; 

unsigned long ftrace_graph_ret_addr(struct task_struct *task, int *idx,
				    unsigned long ret, unsigned long *retp)
{
	int task_idx;

	if (ret != (unsigned long)return_to_handler)
		return ret;

	task_idx = task->curr_ret_stack;

	if (!task->ret_stack || task_idx < *idx)
		return ret;

	task_idx -= *idx;
	(*idx)++;

	return task->ret_stack[task_idx].ret;
}