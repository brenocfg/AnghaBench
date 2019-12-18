#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_rpc_ops {struct nfs_client* (* alloc_client ) (struct nfs_client_initdata const*) ;struct nfs_client* (* init_client ) (struct nfs_client*,struct nfs_client_initdata const*) ;} ;
struct nfs_net {int /*<<< orphan*/  nfs_client_lock; int /*<<< orphan*/  nfs_client_list; } ;
struct nfs_client_initdata {int /*<<< orphan*/  init_flags; int /*<<< orphan*/ * hostname; TYPE_1__* nfs_mod; int /*<<< orphan*/  net; } ;
struct nfs_client {int /*<<< orphan*/  cl_flags; int /*<<< orphan*/  cl_share_link; TYPE_2__* rpc_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_client ) (struct nfs_client*) ;} ;
struct TYPE_3__ {struct nfs_rpc_ops* rpc_ops; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_client*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_client* nfs_found_client (struct nfs_client_initdata const*,struct nfs_client*) ; 
 struct nfs_client* nfs_match_client (struct nfs_client_initdata const*) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_client*) ; 
 struct nfs_client* stub2 (struct nfs_client*,struct nfs_client_initdata const*) ; 
 struct nfs_client* stub3 (struct nfs_client_initdata const*) ; 

struct nfs_client *nfs_get_client(const struct nfs_client_initdata *cl_init)
{
	struct nfs_client *clp, *new = NULL;
	struct nfs_net *nn = net_generic(cl_init->net, nfs_net_id);
	const struct nfs_rpc_ops *rpc_ops = cl_init->nfs_mod->rpc_ops;

	if (cl_init->hostname == NULL) {
		WARN_ON(1);
		return NULL;
	}

	/* see if the client already exists */
	do {
		spin_lock(&nn->nfs_client_lock);

		clp = nfs_match_client(cl_init);
		if (clp) {
			spin_unlock(&nn->nfs_client_lock);
			if (new)
				new->rpc_ops->free_client(new);
			if (IS_ERR(clp))
				return clp;
			return nfs_found_client(cl_init, clp);
		}
		if (new) {
			list_add_tail(&new->cl_share_link,
					&nn->nfs_client_list);
			spin_unlock(&nn->nfs_client_lock);
			new->cl_flags = cl_init->init_flags;
			return rpc_ops->init_client(new, cl_init);
		}

		spin_unlock(&nn->nfs_client_lock);

		new = rpc_ops->alloc_client(cl_init);
	} while (!IS_ERR(new));

	return new;
}