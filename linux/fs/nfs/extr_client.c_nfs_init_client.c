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
struct nfs_client_initdata {int dummy; } ;
struct nfs_client {scalar_t__ cl_cons_state; } ;

/* Variables and functions */
 struct nfs_client* ERR_PTR (int) ; 
 scalar_t__ NFS_CS_READY ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int nfs_create_rpc_client (struct nfs_client*,struct nfs_client_initdata const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_mark_client_ready (struct nfs_client*,scalar_t__) ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 

struct nfs_client *nfs_init_client(struct nfs_client *clp,
				   const struct nfs_client_initdata *cl_init)
{
	int error;

	/* the client is already initialised */
	if (clp->cl_cons_state == NFS_CS_READY)
		return clp;

	/*
	 * Create a client RPC handle for doing FSSTAT with UNIX auth only
	 * - RFC 2623, sec 2.3.2
	 */
	error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_UNIX);
	nfs_mark_client_ready(clp, error == 0 ? NFS_CS_READY : error);
	if (error < 0) {
		nfs_put_client(clp);
		clp = ERR_PTR(error);
	}
	return clp;
}