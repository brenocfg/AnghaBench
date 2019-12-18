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
struct rpc_task_setup {int flags; int priority; struct rpc_clnt* rpc_client; int /*<<< orphan*/  workqueue; struct nfs_commit_data* callback_data; struct rpc_call_ops const* callback_ops; struct rpc_message* rpc_message; int /*<<< orphan*/ * task; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {int /*<<< orphan*/  rpc_cred; int /*<<< orphan*/ * rpc_resp; int /*<<< orphan*/ * rpc_argp; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_call_ops {int dummy; } ;
struct nfs_rpc_ops {int /*<<< orphan*/  (* commit_setup ) (struct nfs_commit_data*,struct rpc_message*,struct rpc_clnt**) ;} ;
struct nfs_commit_data {int /*<<< orphan*/  task; int /*<<< orphan*/  cred; int /*<<< orphan*/  res; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int FLUSH_SYNC ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int flush_task_priority (int) ; 
 int /*<<< orphan*/  nfsiod_workqueue ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  rpc_wait_for_completion_task (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_commit_data*,struct rpc_message*,struct rpc_clnt**) ; 
 int /*<<< orphan*/  trace_nfs_initiate_commit (struct nfs_commit_data*) ; 

int nfs_initiate_commit(struct rpc_clnt *clnt, struct nfs_commit_data *data,
			const struct nfs_rpc_ops *nfs_ops,
			const struct rpc_call_ops *call_ops,
			int how, int flags)
{
	struct rpc_task *task;
	int priority = flush_task_priority(how);
	struct rpc_message msg = {
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
		.rpc_cred = data->cred,
	};
	struct rpc_task_setup task_setup_data = {
		.task = &data->task,
		.rpc_client = clnt,
		.rpc_message = &msg,
		.callback_ops = call_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | flags,
		.priority = priority,
	};
	/* Set up the initial task struct.  */
	nfs_ops->commit_setup(data, &msg, &task_setup_data.rpc_client);
	trace_nfs_initiate_commit(data);

	dprintk("NFS: initiated commit call\n");

	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	if (how & FLUSH_SYNC)
		rpc_wait_for_completion_task(task);
	rpc_put_task(task);
	return 0;
}