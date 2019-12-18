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
struct nfs_net {int /*<<< orphan*/  nfs_client_lock; } ;
struct nfs_client {TYPE_1__* rpc_ops; int /*<<< orphan*/  cl_superblocks; int /*<<< orphan*/  cl_share_link; int /*<<< orphan*/  cl_count; int /*<<< orphan*/  cl_net; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_client ) (struct nfs_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct nfs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_cb_idr_remove_locked (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_client*) ; 

void nfs_put_client(struct nfs_client *clp)
{
	struct nfs_net *nn;

	if (!clp)
		return;

	nn = net_generic(clp->cl_net, nfs_net_id);

	if (refcount_dec_and_lock(&clp->cl_count, &nn->nfs_client_lock)) {
		list_del(&clp->cl_share_link);
		nfs_cb_idr_remove_locked(clp);
		spin_unlock(&nn->nfs_client_lock);

		WARN_ON_ONCE(!list_empty(&clp->cl_superblocks));

		clp->rpc_ops->free_client(clp);
	}
}