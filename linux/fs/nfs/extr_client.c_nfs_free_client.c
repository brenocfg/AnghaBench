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
struct nfs_client {struct nfs_client* cl_acceptor; struct nfs_client* cl_hostname; int /*<<< orphan*/  cl_nfs_mod; int /*<<< orphan*/  cl_net; int /*<<< orphan*/  cl_rpcclient; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_fscache_release_client_cookie (struct nfs_client*) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (int /*<<< orphan*/ ) ; 

void nfs_free_client(struct nfs_client *clp)
{
	nfs_fscache_release_client_cookie(clp);

	/* -EIO all pending I/O */
	if (!IS_ERR(clp->cl_rpcclient))
		rpc_shutdown_client(clp->cl_rpcclient);

	put_net(clp->cl_net);
	put_nfs_version(clp->cl_nfs_mod);
	kfree(clp->cl_hostname);
	kfree(clp->cl_acceptor);
	kfree(clp);
}