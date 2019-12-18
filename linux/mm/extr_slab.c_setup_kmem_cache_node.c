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
struct kmem_cache_node {int /*<<< orphan*/  list_lock; struct alien_cache** alien; struct array_cache* shared; } ;
struct kmem_cache {int shared; int batchcount; int /*<<< orphan*/  limit; } ;
struct array_cache {scalar_t__ avail; int /*<<< orphan*/  entry; } ;
struct alien_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct alien_cache** alloc_alien_cache (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct array_cache* alloc_arraycache (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_alien_cache (struct alien_cache**) ; 
 int /*<<< orphan*/  free_block (struct kmem_cache*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 struct kmem_cache_node* get_node (struct kmem_cache*,int) ; 
 int init_cache_node (struct kmem_cache*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct array_cache*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  slabs_destroy (struct kmem_cache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ use_alien_caches ; 

__attribute__((used)) static int setup_kmem_cache_node(struct kmem_cache *cachep,
				int node, gfp_t gfp, bool force_change)
{
	int ret = -ENOMEM;
	struct kmem_cache_node *n;
	struct array_cache *old_shared = NULL;
	struct array_cache *new_shared = NULL;
	struct alien_cache **new_alien = NULL;
	LIST_HEAD(list);

	if (use_alien_caches) {
		new_alien = alloc_alien_cache(node, cachep->limit, gfp);
		if (!new_alien)
			goto fail;
	}

	if (cachep->shared) {
		new_shared = alloc_arraycache(node,
			cachep->shared * cachep->batchcount, 0xbaadf00d, gfp);
		if (!new_shared)
			goto fail;
	}

	ret = init_cache_node(cachep, node, gfp);
	if (ret)
		goto fail;

	n = get_node(cachep, node);
	spin_lock_irq(&n->list_lock);
	if (n->shared && force_change) {
		free_block(cachep, n->shared->entry,
				n->shared->avail, node, &list);
		n->shared->avail = 0;
	}

	if (!n->shared || force_change) {
		old_shared = n->shared;
		n->shared = new_shared;
		new_shared = NULL;
	}

	if (!n->alien) {
		n->alien = new_alien;
		new_alien = NULL;
	}

	spin_unlock_irq(&n->list_lock);
	slabs_destroy(cachep, &list);

	/*
	 * To protect lockless access to n->shared during irq disabled context.
	 * If n->shared isn't NULL in irq disabled context, accessing to it is
	 * guaranteed to be valid until irq is re-enabled, because it will be
	 * freed after synchronize_rcu().
	 */
	if (old_shared && force_change)
		synchronize_rcu();

fail:
	kfree(old_shared);
	kfree(new_shared);
	free_alien_cache(new_alien);

	return ret;
}