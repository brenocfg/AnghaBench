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
struct rpc_task {int tk_status; int /*<<< orphan*/  tk_waitqueue; int /*<<< orphan*/  tk_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_exit_task ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ ,struct rpc_task*) ; 

void rpc_exit(struct rpc_task *task, int status)
{
	task->tk_status = status;
	task->tk_action = rpc_exit_task;
	rpc_wake_up_queued_task(task->tk_waitqueue, task);
}