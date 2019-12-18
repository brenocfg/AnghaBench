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
struct TYPE_3__ {int so_id; int /*<<< orphan*/  so_clid; } ;
struct TYPE_4__ {TYPE_1__ si_opaque; } ;
struct nfs4_stid {void (* sc_free ) (struct nfs4_stid*) ;int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_count; TYPE_2__ sc_stateid; struct nfs4_client* sc_client; } ;
struct nfs4_client {int /*<<< orphan*/  cl_clientid; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_stateids; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct nfs4_stid*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct nfs4_stid*) ; 
 struct nfs4_stid* kmem_cache_zalloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs4_stid *nfs4_alloc_stid(struct nfs4_client *cl, struct kmem_cache *slab,
				  void (*sc_free)(struct nfs4_stid *))
{
	struct nfs4_stid *stid;
	int new_id;

	stid = kmem_cache_zalloc(slab, GFP_KERNEL);
	if (!stid)
		return NULL;

	idr_preload(GFP_KERNEL);
	spin_lock(&cl->cl_lock);
	/* Reserving 0 for start of file in nfsdfs "states" file: */
	new_id = idr_alloc_cyclic(&cl->cl_stateids, stid, 1, 0, GFP_NOWAIT);
	spin_unlock(&cl->cl_lock);
	idr_preload_end();
	if (new_id < 0)
		goto out_free;

	stid->sc_free = sc_free;
	stid->sc_client = cl;
	stid->sc_stateid.si_opaque.so_id = new_id;
	stid->sc_stateid.si_opaque.so_clid = cl->cl_clientid;
	/* Will be incremented before return to client: */
	refcount_set(&stid->sc_count, 1);
	spin_lock_init(&stid->sc_lock);

	/*
	 * It shouldn't be a problem to reuse an opaque stateid value.
	 * I don't think it is for 4.1.  But with 4.0 I worry that, for
	 * example, a stray write retransmission could be accepted by
	 * the server when it should have been rejected.  Therefore,
	 * adopt a trick from the sctp code to attempt to maximize the
	 * amount of time until an id is reused, by ensuring they always
	 * "increase" (mod INT_MAX):
	 */
	return stid;
out_free:
	kmem_cache_free(slab, stid);
	return NULL;
}