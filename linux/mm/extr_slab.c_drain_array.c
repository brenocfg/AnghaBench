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
struct kmem_cache_node {int /*<<< orphan*/  list_lock; } ;
struct kmem_cache {int dummy; } ;
struct array_cache {scalar_t__ touched; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mutex_acquired () ; 
 int /*<<< orphan*/  drain_array_locked (struct kmem_cache*,struct array_cache*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  slabs_destroy (struct kmem_cache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drain_array(struct kmem_cache *cachep, struct kmem_cache_node *n,
			 struct array_cache *ac, int node)
{
	LIST_HEAD(list);

	/* ac from n->shared can be freed if we don't hold the slab_mutex. */
	check_mutex_acquired();

	if (!ac || !ac->avail)
		return;

	if (ac->touched) {
		ac->touched = 0;
		return;
	}

	spin_lock_irq(&n->list_lock);
	drain_array_locked(cachep, ac, node, false, &list);
	spin_unlock_irq(&n->list_lock);

	slabs_destroy(cachep, &list);
}