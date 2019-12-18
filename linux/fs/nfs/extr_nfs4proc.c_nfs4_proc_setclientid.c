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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_task_setup {int flags; struct nfs4_setclientid* callback_data; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; TYPE_3__* rpc_client; } ;
struct rpc_message {struct cred const* rpc_cred; struct nfs4_setclientid_res* rpc_resp; struct nfs4_setclientid* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_client {int /*<<< orphan*/  cl_acceptor; int /*<<< orphan*/  cl_owner_id; TYPE_3__* cl_rpcclient; int /*<<< orphan*/  cl_ipaddr; int /*<<< orphan*/  cl_flags; } ;
struct nfs4_setclientid_res {int dummy; } ;
struct nfs4_setclientid {scalar_t__ sc_cred; int /*<<< orphan*/  sc_uaddr; int /*<<< orphan*/  sc_uaddr_len; int /*<<< orphan*/  sc_netid; int /*<<< orphan*/  sc_netid_len; struct nfs_client* sc_clnt; int /*<<< orphan*/  sc_prog; int /*<<< orphan*/ * sc_verifier; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;
struct TYPE_6__ {TYPE_2__* cl_auth; } ;
struct TYPE_5__ {TYPE_1__* au_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  au_name; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_SETCLIENTID ; 
 int /*<<< orphan*/  NFS_CS_MIGRATION ; 
 int RPC_TASK_NO_ROUND_ROBIN ; 
 int RPC_TASK_TIMEOUT ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int nfs4_call_sync_custom (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  nfs4_init_boot_verifier (struct nfs_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_init_callback_netid (struct nfs_client*,int /*<<< orphan*/ ,int) ; 
 int nfs4_init_nonuniform_client_string (struct nfs_client*) ; 
 int nfs4_init_uniform_client_string (struct nfs_client*) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_setclientid_ops ; 
 int /*<<< orphan*/  put_rpccred (scalar_t__) ; 
 int /*<<< orphan*/  rpcauth_stringify_acceptor (scalar_t__) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs4_setclientid (struct nfs_client*,int) ; 

int nfs4_proc_setclientid(struct nfs_client *clp, u32 program,
		unsigned short port, const struct cred *cred,
		struct nfs4_setclientid_res *res)
{
	nfs4_verifier sc_verifier;
	struct nfs4_setclientid setclientid = {
		.sc_verifier = &sc_verifier,
		.sc_prog = program,
		.sc_clnt = clp,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SETCLIENTID],
		.rpc_argp = &setclientid,
		.rpc_resp = res,
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_setclientid_ops,
		.callback_data = &setclientid,
		.flags = RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN,
	};
	int status;

	/* nfs_client_id4 */
	nfs4_init_boot_verifier(clp, &sc_verifier);

	if (test_bit(NFS_CS_MIGRATION, &clp->cl_flags))
		status = nfs4_init_uniform_client_string(clp);
	else
		status = nfs4_init_nonuniform_client_string(clp);

	if (status)
		goto out;

	/* cb_client4 */
	setclientid.sc_netid_len =
				nfs4_init_callback_netid(clp,
						setclientid.sc_netid,
						sizeof(setclientid.sc_netid));
	setclientid.sc_uaddr_len = scnprintf(setclientid.sc_uaddr,
				sizeof(setclientid.sc_uaddr), "%s.%u.%u",
				clp->cl_ipaddr, port >> 8, port & 255);

	dprintk("NFS call  setclientid auth=%s, '%s'\n",
		clp->cl_rpcclient->cl_auth->au_ops->au_name,
		clp->cl_owner_id);

	status = nfs4_call_sync_custom(&task_setup_data);
	if (setclientid.sc_cred) {
		kfree(clp->cl_acceptor);
		clp->cl_acceptor = rpcauth_stringify_acceptor(setclientid.sc_cred);
		put_rpccred(setclientid.sc_cred);
	}
out:
	trace_nfs4_setclientid(clp, status);
	dprintk("NFS reply setclientid: %d\n", status);
	return status;
}