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
struct rpc_message {struct cred const* rpc_cred; struct nfs_client* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_client {int /*<<< orphan*/  cl_rpcclient; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_RENEW ; 
 int /*<<< orphan*/  RPC_TASK_TIMEOUT ; 
 int /*<<< orphan*/  do_renew_lease (struct nfs_client*,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_proc_renew(struct nfs_client *clp, const struct cred *cred)
{
	struct rpc_message msg = {
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_RENEW],
		.rpc_argp	= clp,
		.rpc_cred	= cred,
	};
	unsigned long now = jiffies;
	int status;

	status = rpc_call_sync(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT);
	if (status < 0)
		return status;
	do_renew_lease(clp, now);
	return 0;
}