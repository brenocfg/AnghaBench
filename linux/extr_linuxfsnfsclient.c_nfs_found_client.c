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
 int ERESTARTSYS ; 
 struct nfs_client* ERR_PTR (int) ; 
 scalar_t__ NFS_CS_READY ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int nfs_wait_client_init_complete (struct nfs_client*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static struct nfs_client *
nfs_found_client(const struct nfs_client_initdata *cl_init,
		 struct nfs_client *clp)
{
	int error;

	error = nfs_wait_client_init_complete(clp);
	if (error < 0) {
		nfs_put_client(clp);
		return ERR_PTR(-ERESTARTSYS);
	}

	if (clp->cl_cons_state < NFS_CS_READY) {
		error = clp->cl_cons_state;
		nfs_put_client(clp);
		return ERR_PTR(error);
	}

	smp_rmb();
	return clp;
}