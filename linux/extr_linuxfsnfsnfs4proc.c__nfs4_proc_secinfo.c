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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {struct rpc_cred* rpc_cred; struct nfs4_secinfo_res* rpc_resp; struct nfs4_secinfo_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct qstr {int name; } ;
struct nfs4_secinfo_res {int /*<<< orphan*/  seq_res; struct nfs4_secinfo_flavors* flavors; } ;
struct nfs4_secinfo_flavors {int dummy; } ;
struct nfs4_secinfo_arg {int /*<<< orphan*/  seq_args; struct qstr const* name; int /*<<< orphan*/  dir_fh; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {TYPE_1__* nfs_client; struct rpc_clnt* client; } ;
struct TYPE_5__ {struct rpc_clnt* cl_rpcclient; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_SECINFO ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 TYPE_3__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  NFS_SP4_MACH_CRED_SECINFO ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int nfs4_call_sync (struct rpc_clnt*,TYPE_3__*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rpc_cred* nfs4_get_clid_cred (TYPE_1__*) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_state_protect (TYPE_1__*,int /*<<< orphan*/ ,struct rpc_clnt**,struct rpc_message*) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 

__attribute__((used)) static int _nfs4_proc_secinfo(struct inode *dir, const struct qstr *name, struct nfs4_secinfo_flavors *flavors, bool use_integrity)
{
	int status;
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
	struct rpc_clnt *clnt = NFS_SERVER(dir)->client;
	struct rpc_cred *cred = NULL;

	if (use_integrity) {
		clnt = NFS_SERVER(dir)->nfs_client->cl_rpcclient;
		cred = nfs4_get_clid_cred(NFS_SERVER(dir)->nfs_client);
		msg.rpc_cred = cred;
	}

	dprintk("NFS call  secinfo %s\n", name->name);

	nfs4_state_protect(NFS_SERVER(dir)->nfs_client,
		NFS_SP4_MACH_CRED_SECINFO, &clnt, &msg);

	status = nfs4_call_sync(clnt, NFS_SERVER(dir), &msg, &args.seq_args,
				&res.seq_res, 0);
	dprintk("NFS reply  secinfo: %d\n", status);

	if (cred)
		put_rpccred(cred);

	return status;
}