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
struct rpc_task_setup {void* callback_data; int flags; struct rpc_call_ops const* callback_ops; struct rpc_message const* rpc_message; struct rpc_clnt* rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_call_ops {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 

int
rpc_call_async(struct rpc_clnt *clnt, const struct rpc_message *msg, int flags,
	       const struct rpc_call_ops *tk_ops, void *data)
{
	struct rpc_task	*task;
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clnt,
		.rpc_message = msg,
		.callback_ops = tk_ops,
		.callback_data = data,
		.flags = flags|RPC_TASK_ASYNC,
	};

	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	rpc_put_task(task);
	return 0;
}