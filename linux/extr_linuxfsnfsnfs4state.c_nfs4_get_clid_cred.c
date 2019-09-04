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
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 struct rpc_cred* nfs4_get_machine_cred_locked (struct nfs_client*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct rpc_cred *nfs4_get_clid_cred(struct nfs_client *clp)
{
	struct rpc_cred *cred;

	spin_lock(&clp->cl_lock);
	cred = nfs4_get_machine_cred_locked(clp);
	spin_unlock(&clp->cl_lock);
	return cred;
}