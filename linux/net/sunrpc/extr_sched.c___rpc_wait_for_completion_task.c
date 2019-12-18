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
typedef  int /*<<< orphan*/  wait_bit_action_f ;
struct rpc_task {int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_ACTIVE ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int out_of_line_wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rpc_wait_bit_killable ; 

int __rpc_wait_for_completion_task(struct rpc_task *task, wait_bit_action_f *action)
{
	if (action == NULL)
		action = rpc_wait_bit_killable;
	return out_of_line_wait_on_bit(&task->tk_runstate, RPC_TASK_ACTIVE,
			action, TASK_KILLABLE);
}