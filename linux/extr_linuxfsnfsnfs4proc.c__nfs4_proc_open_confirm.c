#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_task_setup {int /*<<< orphan*/  flags; int /*<<< orphan*/  workqueue; struct nfs4_opendata* callback_data; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; int /*<<< orphan*/  rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {int /*<<< orphan*/  rpc_cred; TYPE_3__* rpc_resp; TYPE_2__* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_args; } ;
struct nfs4_opendata {int rpc_done; int rpc_status; int cancelled; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  kref; int /*<<< orphan*/  is_recover; TYPE_3__ c_res; TYPE_2__ c_arg; TYPE_1__* owner; int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_cred; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 size_t NFSPROC4_CLNT_OPEN_CONFIRM ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_open_confirm_ops ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfsiod_workqueue ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int rpc_wait_for_completion_task (struct rpc_task*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int _nfs4_proc_open_confirm(struct nfs4_opendata *data)
{
	struct nfs_server *server = NFS_SERVER(d_inode(data->dir));
	struct rpc_task *task;
	struct  rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OPEN_CONFIRM],
		.rpc_argp = &data->c_arg,
		.rpc_resp = &data->c_res,
		.rpc_cred = data->owner->so_cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_open_confirm_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC,
	};
	int status;

	nfs4_init_sequence(&data->c_arg.seq_args, &data->c_res.seq_res, 1,
				data->is_recover);
	kref_get(&data->kref);
	data->rpc_done = false;
	data->rpc_status = 0;
	data->timestamp = jiffies;
	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	status = rpc_wait_for_completion_task(task);
	if (status != 0) {
		data->cancelled = true;
		smp_wmb();
	} else
		status = data->rpc_status;
	rpc_put_task(task);
	return status;
}