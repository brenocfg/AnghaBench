#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {int dummy; } ;
struct nfs_net {unsigned short nfs_callback_tcpport; unsigned short nfs_callback_tcpport6; } ;
struct TYPE_2__ {scalar_t__ ss_family; } ;
struct nfs_client {int /*<<< orphan*/  cl_confirm; int /*<<< orphan*/  cl_clientid; TYPE_1__ cl_addr; int /*<<< orphan*/  cl_net; } ;
struct nfs4_setclientid_res {int /*<<< orphan*/  confirm; int /*<<< orphan*/  clientid; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  NFS4_CALLBACK ; 
 struct nfs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs40_walk_client_list (struct nfs_client*,struct nfs_client**,struct rpc_cred*) ; 
 int nfs4_proc_setclientid (struct nfs_client*,int /*<<< orphan*/ ,unsigned short,struct rpc_cred*,struct nfs4_setclientid_res*) ; 
 int /*<<< orphan*/  nfs4_schedule_state_renewal (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_net_id ; 

int nfs40_discover_server_trunking(struct nfs_client *clp,
				   struct nfs_client **result,
				   struct rpc_cred *cred)
{
	struct nfs4_setclientid_res clid = {
		.clientid = clp->cl_clientid,
		.confirm = clp->cl_confirm,
	};
	struct nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
	unsigned short port;
	int status;

	port = nn->nfs_callback_tcpport;
	if (clp->cl_addr.ss_family == AF_INET6)
		port = nn->nfs_callback_tcpport6;

	status = nfs4_proc_setclientid(clp, NFS4_CALLBACK, port, cred, &clid);
	if (status != 0)
		goto out;
	clp->cl_clientid = clid.clientid;
	clp->cl_confirm = clid.confirm;

	status = nfs40_walk_client_list(clp, result, cred);
	if (status == 0) {
		/* Sustain the lease, even if it's empty.  If the clientid4
		 * goes stale it's of no use for trunking discovery. */
		nfs4_schedule_state_renewal(*result);
	}
out:
	return status;
}