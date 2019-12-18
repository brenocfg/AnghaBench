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
struct xdr_netobj {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct nfs4_client {TYPE_1__ cl_name; int /*<<< orphan*/  cl_cb_waitq; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  async_lock; int /*<<< orphan*/  async_copies; int /*<<< orphan*/  cl_lo_states; int /*<<< orphan*/  cl_revoked; int /*<<< orphan*/  cl_lru; int /*<<< orphan*/  cl_delegations; int /*<<< orphan*/  cl_openowners; int /*<<< orphan*/  cl_idhash; int /*<<< orphan*/  cl_cb_state; int /*<<< orphan*/  cl_rpc_users; int /*<<< orphan*/  cl_stateids; int /*<<< orphan*/  cl_sessions; int /*<<< orphan*/ * cl_ownerstr_hashtbl; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSD4_CB_UNKNOWN ; 
 int OWNER_HASH_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_slab ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_client*) ; 
 struct nfs4_client* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_netobj_dup (TYPE_1__*,struct xdr_netobj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_client *alloc_client(struct xdr_netobj name)
{
	struct nfs4_client *clp;
	int i;

	clp = kmem_cache_zalloc(client_slab, GFP_KERNEL);
	if (clp == NULL)
		return NULL;
	xdr_netobj_dup(&clp->cl_name, &name, GFP_KERNEL);
	if (clp->cl_name.data == NULL)
		goto err_no_name;
	clp->cl_ownerstr_hashtbl = kmalloc_array(OWNER_HASH_SIZE,
						 sizeof(struct list_head),
						 GFP_KERNEL);
	if (!clp->cl_ownerstr_hashtbl)
		goto err_no_hashtbl;
	for (i = 0; i < OWNER_HASH_SIZE; i++)
		INIT_LIST_HEAD(&clp->cl_ownerstr_hashtbl[i]);
	INIT_LIST_HEAD(&clp->cl_sessions);
	idr_init(&clp->cl_stateids);
	atomic_set(&clp->cl_rpc_users, 0);
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	INIT_LIST_HEAD(&clp->cl_idhash);
	INIT_LIST_HEAD(&clp->cl_openowners);
	INIT_LIST_HEAD(&clp->cl_delegations);
	INIT_LIST_HEAD(&clp->cl_lru);
	INIT_LIST_HEAD(&clp->cl_revoked);
#ifdef CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&clp->cl_lo_states);
#endif
	INIT_LIST_HEAD(&clp->async_copies);
	spin_lock_init(&clp->async_lock);
	spin_lock_init(&clp->cl_lock);
	rpc_init_wait_queue(&clp->cl_cb_waitq, "Backchannel slot table");
	return clp;
err_no_hashtbl:
	kfree(clp->cl_name.data);
err_no_name:
	kmem_cache_free(client_slab, clp);
	return NULL;
}