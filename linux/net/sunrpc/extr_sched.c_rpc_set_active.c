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
struct rpc_task {int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_ACTIVE ; 
 int /*<<< orphan*/  rpc_task_set_debuginfo (struct rpc_task*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rpc_task_begin (struct rpc_task*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpc_set_active(struct rpc_task *task)
{
	rpc_task_set_debuginfo(task);
	set_bit(RPC_TASK_ACTIVE, &task->tk_runstate);
	trace_rpc_task_begin(task, NULL);
}