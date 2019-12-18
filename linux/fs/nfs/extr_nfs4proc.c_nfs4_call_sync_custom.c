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
struct rpc_task_setup {int dummy; } ;
struct rpc_task {int tk_status; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 

__attribute__((used)) static int nfs4_call_sync_custom(struct rpc_task_setup *task_setup)
{
	int ret;
	struct rpc_task *task;

	task = rpc_run_task(task_setup);
	if (IS_ERR(task))
		return PTR_ERR(task);

	ret = task->tk_status;
	rpc_put_task(task);
	return ret;
}