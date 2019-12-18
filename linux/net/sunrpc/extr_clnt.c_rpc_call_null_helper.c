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
struct rpc_xprt {int dummy; } ;
struct rpc_task_setup {void* callback_data; int flags; struct rpc_call_ops const* callback_ops; struct rpc_cred* rpc_op_cred; struct rpc_message* rpc_message; struct rpc_xprt* rpc_xprt; struct rpc_clnt* rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_call_ops {int dummy; } ;

/* Variables and functions */
 int RPC_TASK_NULLCREDS ; 
 struct rpc_call_ops const rpc_default_ops ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  rpcproc_null ; 

__attribute__((used)) static
struct rpc_task *rpc_call_null_helper(struct rpc_clnt *clnt,
		struct rpc_xprt *xprt, struct rpc_cred *cred, int flags,
		const struct rpc_call_ops *ops, void *data)
{
	struct rpc_message msg = {
		.rpc_proc = &rpcproc_null,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clnt,
		.rpc_xprt = xprt,
		.rpc_message = &msg,
		.rpc_op_cred = cred,
		.callback_ops = (ops != NULL) ? ops : &rpc_default_ops,
		.callback_data = data,
		.flags = flags | RPC_TASK_NULLCREDS,
	};

	return rpc_run_task(&task_setup_data);
}