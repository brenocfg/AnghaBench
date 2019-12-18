#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int /*<<< orphan*/ * tk_action; int /*<<< orphan*/  tk_calldata; TYPE_2__* tk_ops; TYPE_1__* tk_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rpc_call_done ) (struct rpc_task*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rpc_count_stats ) (struct rpc_task*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  cl_metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_count_iostats (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_reset_task_statistics (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_release (struct rpc_task*) ; 

void rpc_exit_task(struct rpc_task *task)
{
	task->tk_action = NULL;
	if (task->tk_ops->rpc_count_stats)
		task->tk_ops->rpc_count_stats(task, task->tk_calldata);
	else if (task->tk_client)
		rpc_count_iostats(task, task->tk_client->cl_metrics);
	if (task->tk_ops->rpc_call_done != NULL) {
		task->tk_ops->rpc_call_done(task, task->tk_calldata);
		if (task->tk_action != NULL) {
			/* Always release the RPC slot and buffer memory */
			xprt_release(task);
			rpc_reset_task_statistics(task);
		}
	}
}