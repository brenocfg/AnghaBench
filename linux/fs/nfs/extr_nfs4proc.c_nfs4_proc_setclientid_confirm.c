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
struct rpc_message {struct cred const* rpc_cred; struct nfs4_setclientid_res* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_client {TYPE_3__* cl_rpcclient; int /*<<< orphan*/  cl_clientid; } ;
struct nfs4_setclientid_res {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cl_auth; } ;
struct TYPE_5__ {TYPE_1__* au_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  au_name; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_SETCLIENTID_CONFIRM ; 
 int RPC_TASK_NO_ROUND_ROBIN ; 
 int RPC_TASK_TIMEOUT ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int rpc_call_sync (TYPE_3__*,struct rpc_message*,int) ; 
 int /*<<< orphan*/  trace_nfs4_setclientid_confirm (struct nfs_client*,int) ; 

int nfs4_proc_setclientid_confirm(struct nfs_client *clp,
		struct nfs4_setclientid_res *arg,
		const struct cred *cred)
{
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SETCLIENTID_CONFIRM],
		.rpc_argp = arg,
		.rpc_cred = cred,
	};
	int status;

	dprintk("NFS call  setclientid_confirm auth=%s, (client ID %llx)\n",
		clp->cl_rpcclient->cl_auth->au_ops->au_name,
		clp->cl_clientid);
	status = rpc_call_sync(clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_setclientid_confirm(clp, status);
	dprintk("NFS reply setclientid_confirm: %d\n", status);
	return status;
}