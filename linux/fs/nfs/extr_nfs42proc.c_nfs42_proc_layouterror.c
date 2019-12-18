#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task_setup {int /*<<< orphan*/  rpc_client; struct nfs42_layouterror_data* callback_data; int /*<<< orphan*/  flags; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {TYPE_3__* rpc_resp; TYPE_2__* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct pnfs_layout_segment {TYPE_1__* pls_layout; } ;
struct TYPE_7__ {int /*<<< orphan*/  seq_res; int /*<<< orphan*/  num_errors; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  num_errors; struct nfs42_layout_error* errors; } ;
struct nfs42_layouterror_data {TYPE_3__ res; TYPE_2__ args; } ;
struct nfs42_layout_error {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  client; } ;
struct TYPE_5__ {struct inode* plh_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 size_t NFS42_LAYOUTERROR_MAX ; 
 size_t NFSPROC4_CLNT_LAYOUTERROR ; 
 int /*<<< orphan*/  NFS_CAP_LAYOUTERROR ; 
 TYPE_4__* NFS_SERVER (struct inode*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 struct nfs42_layouterror_data* nfs42_alloc_layouterror_data (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs42_layouterror_ops ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 

int nfs42_proc_layouterror(struct pnfs_layout_segment *lseg,
		const struct nfs42_layout_error *errors, size_t n)
{
	struct inode *inode = lseg->pls_layout->plh_inode;
	struct nfs42_layouterror_data *data;
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTERROR],
	};
	struct rpc_task_setup task_setup = {
		.rpc_message = &msg,
		.callback_ops = &nfs42_layouterror_ops,
		.flags = RPC_TASK_ASYNC,
	};
	unsigned int i;

	if (!nfs_server_capable(inode, NFS_CAP_LAYOUTERROR))
		return -EOPNOTSUPP;
	if (n > NFS42_LAYOUTERROR_MAX)
		return -EINVAL;
	data = nfs42_alloc_layouterror_data(lseg, GFP_NOFS);
	if (!data)
		return -ENOMEM;
	for (i = 0; i < n; i++) {
		data->args.errors[i] = errors[i];
		data->args.num_errors++;
		data->res.num_errors++;
	}
	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	task_setup.callback_data = data;
	task_setup.rpc_client = NFS_SERVER(inode)->client;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0, 0);
	task = rpc_run_task(&task_setup);
	if (IS_ERR(task))
		return PTR_ERR(task);
	rpc_put_task(task);
	return 0;
}