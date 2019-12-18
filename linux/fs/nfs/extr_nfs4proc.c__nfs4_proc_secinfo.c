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
struct rpc_task_setup {struct rpc_clnt* rpc_client; int /*<<< orphan*/  flags; struct nfs4_call_sync_data* callback_data; int /*<<< orphan*/  callback_ops; struct rpc_message* rpc_message; } ;
struct rpc_message {struct cred const* rpc_cred; struct nfs4_secinfo_res* rpc_resp; struct nfs4_secinfo_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct qstr {int name; } ;
struct nfs_client {struct rpc_clnt* cl_rpcclient; TYPE_1__* cl_mvops; } ;
struct nfs4_secinfo_res {int /*<<< orphan*/  seq_res; struct nfs4_secinfo_flavors* flavors; } ;
struct nfs4_secinfo_flavors {int dummy; } ;
struct nfs4_secinfo_arg {int /*<<< orphan*/  seq_args; struct qstr const* name; int /*<<< orphan*/  dir_fh; } ;
struct nfs4_call_sync_data {int /*<<< orphan*/ * seq_res; int /*<<< orphan*/ * seq_args; TYPE_2__* seq_server; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {struct nfs_client* nfs_client; struct rpc_clnt* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  call_sync_ops; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_SECINFO ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  NFS_SP4_MACH_CRED_SECINFO ; 
 int /*<<< orphan*/  RPC_TASK_NO_ROUND_ROBIN ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int nfs4_call_sync_custom (struct rpc_task_setup*) ; 
 struct cred* nfs4_get_clid_cred (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_state_protect (struct nfs_client*,int /*<<< orphan*/ ,struct rpc_clnt**,struct rpc_message*) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 

__attribute__((used)) static int _nfs4_proc_secinfo(struct inode *dir, const struct qstr *name, struct nfs4_secinfo_flavors *flavors, bool use_integrity)
{
	int status;
	struct rpc_clnt *clnt = NFS_SERVER(dir)->client;
	struct nfs_client *clp = NFS_SERVER(dir)->nfs_client;
	struct nfs4_secinfo_arg args = {
		.dir_fh = NFS_FH(dir),
		.name   = name,
	};
	struct nfs4_secinfo_res res = {
		.flavors     = flavors,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SECINFO],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};
	struct nfs4_call_sync_data data = {
		.seq_server = NFS_SERVER(dir),
		.seq_args = &args.seq_args,
		.seq_res = &res.seq_res,
	};
	struct rpc_task_setup task_setup = {
		.rpc_client = clnt,
		.rpc_message = &msg,
		.callback_ops = clp->cl_mvops->call_sync_ops,
		.callback_data = &data,
		.flags = RPC_TASK_NO_ROUND_ROBIN,
	};
	const struct cred *cred = NULL;

	if (use_integrity) {
		clnt = clp->cl_rpcclient;
		task_setup.rpc_client = clnt;

		cred = nfs4_get_clid_cred(clp);
		msg.rpc_cred = cred;
	}

	dprintk("NFS call  secinfo %s\n", name->name);

	nfs4_state_protect(clp, NFS_SP4_MACH_CRED_SECINFO, &clnt, &msg);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 0);
	status = nfs4_call_sync_custom(&task_setup);

	dprintk("NFS reply  secinfo: %d\n", status);

	put_cred(cred);
	return status;
}