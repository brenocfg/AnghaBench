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
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfs4_client {int /*<<< orphan*/ * cl_nfsd_dentry; int /*<<< orphan*/  cl_lru; int /*<<< orphan*/  cl_rpc_users; int /*<<< orphan*/  cl_lock; scalar_t__ cl_time; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 int /*<<< orphan*/  expiry_wq ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhash_client_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void force_expire_client(struct nfs4_client *clp)
{
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	bool already_expired;

	spin_lock(&clp->cl_lock);
	clp->cl_time = 0;
	spin_unlock(&clp->cl_lock);

	wait_event(expiry_wq, atomic_read(&clp->cl_rpc_users) == 0);
	spin_lock(&nn->client_lock);
	already_expired = list_empty(&clp->cl_lru);
	if (!already_expired)
		unhash_client_locked(clp);
	spin_unlock(&nn->client_lock);

	if (!already_expired)
		expire_client(clp);
	else
		wait_event(expiry_wq, clp->cl_nfsd_dentry == NULL);
}