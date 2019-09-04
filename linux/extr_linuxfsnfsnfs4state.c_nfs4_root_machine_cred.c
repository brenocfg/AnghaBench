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
struct rpc_cred {int dummy; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; struct rpc_cred* cl_machine_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpc_lookup_machine_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_root_machine_cred(struct nfs_client *clp)
{
	struct rpc_cred *cred, *new;

	new = rpc_lookup_machine_cred(NULL);
	spin_lock(&clp->cl_lock);
	cred = clp->cl_machine_cred;
	clp->cl_machine_cred = new;
	spin_unlock(&clp->cl_lock);
	if (cred != NULL)
		put_rpccred(cred);
}