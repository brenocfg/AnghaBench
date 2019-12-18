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
struct rpcbind_args {int dummy; } ;
struct rpc_task_setup {int flags; struct rpcbind_args* callback_data; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; struct rpc_clnt* rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_procinfo {int dummy; } ;
struct rpc_message {struct rpcbind_args* rpc_resp; struct rpcbind_args* rpc_argp; struct rpc_procinfo const* rpc_proc; } ;
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int RPC_TASK_ASYNC ; 
 int RPC_TASK_SOFTCONN ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  rpcb_getport_ops ; 

__attribute__((used)) static struct rpc_task *rpcb_call_async(struct rpc_clnt *rpcb_clnt,
		struct rpcbind_args *map, const struct rpc_procinfo *proc)
{
	struct rpc_message msg = {
		.rpc_proc = proc,
		.rpc_argp = map,
		.rpc_resp = map,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = rpcb_clnt,
		.rpc_message = &msg,
		.callback_ops = &rpcb_getport_ops,
		.callback_data = map,
		.flags = RPC_TASK_ASYNC | RPC_TASK_SOFTCONN,
	};

	return rpc_run_task(&task_setup_data);
}