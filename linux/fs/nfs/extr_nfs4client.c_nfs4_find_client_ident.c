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
struct nfs_net {int /*<<< orphan*/  nfs_client_lock; int /*<<< orphan*/  cb_ident_idr; } ;
struct nfs_client {int /*<<< orphan*/  cl_count; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nfs_client* idr_find (int /*<<< orphan*/ *,int) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs_client *
nfs4_find_client_ident(struct net *net, int cb_ident)
{
	struct nfs_client *clp;
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	spin_lock(&nn->nfs_client_lock);
	clp = idr_find(&nn->cb_ident_idr, cb_ident);
	if (clp)
		refcount_inc(&clp->cl_count);
	spin_unlock(&nn->nfs_client_lock);
	return clp;
}