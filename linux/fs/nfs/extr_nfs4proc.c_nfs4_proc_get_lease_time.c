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
struct rpc_task_setup {int /*<<< orphan*/  flags; struct nfs4_get_lease_time_data* callback_data; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; int /*<<< orphan*/  rpc_client; } ;
struct rpc_message {struct nfs4_get_lease_time_res* rpc_resp; struct nfs4_get_lease_time_args* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_client {int /*<<< orphan*/  cl_rpcclient; } ;
struct nfs4_get_lease_time_res {int /*<<< orphan*/  lr_seq_res; struct nfs_fsinfo* lr_fsinfo; } ;
struct nfs4_get_lease_time_data {struct nfs_client* clp; struct nfs4_get_lease_time_res* res; struct nfs4_get_lease_time_args* args; } ;
struct nfs4_get_lease_time_args {int /*<<< orphan*/  la_seq_args; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_GET_LEASE_TIME ; 
 int /*<<< orphan*/  RPC_TASK_TIMEOUT ; 
 int nfs4_call_sync_custom (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  nfs4_get_lease_time_ops ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

int nfs4_proc_get_lease_time(struct nfs_client *clp, struct nfs_fsinfo *fsinfo)
{
	struct nfs4_get_lease_time_args args;
	struct nfs4_get_lease_time_res res = {
		.lr_fsinfo = fsinfo,
	};
	struct nfs4_get_lease_time_data data = {
		.args = &args,
		.res = &res,
		.clp = clp,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GET_LEASE_TIME],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};
	struct rpc_task_setup task_setup = {
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_get_lease_time_ops,
		.callback_data = &data,
		.flags = RPC_TASK_TIMEOUT,
	};

	nfs4_init_sequence(&args.la_seq_args, &res.lr_seq_res, 0, 1);
	return nfs4_call_sync_custom(&task_setup);
}