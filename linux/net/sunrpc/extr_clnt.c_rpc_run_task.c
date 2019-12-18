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
struct rpc_task_setup {int /*<<< orphan*/  rpc_message; int /*<<< orphan*/  rpc_client; } ;
struct rpc_task {int /*<<< orphan*/  tk_count; int /*<<< orphan*/ * tk_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_execute (struct rpc_task*) ; 
 struct rpc_task* rpc_new_task (struct rpc_task_setup const*) ; 
 int /*<<< orphan*/  rpc_task_set_client (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_task_set_rpc_message (struct rpc_task*,int /*<<< orphan*/ ) ; 

struct rpc_task *rpc_run_task(const struct rpc_task_setup *task_setup_data)
{
	struct rpc_task *task;

	task = rpc_new_task(task_setup_data);

	rpc_task_set_client(task, task_setup_data->rpc_client);
	rpc_task_set_rpc_message(task, task_setup_data->rpc_message);

	if (task->tk_action == NULL)
		rpc_call_start(task);

	atomic_inc(&task->tk_count);
	rpc_execute(task);
	return task;
}