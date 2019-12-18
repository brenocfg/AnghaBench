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
struct page {int /*<<< orphan*/  rcu_head; void* freelist; } ;
struct kmem_cache {int flags; int /*<<< orphan*/  freelist_cache; } ;

/* Variables and functions */
 scalar_t__ OFF_SLAB (struct kmem_cache*) ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kmem_freepages (struct kmem_cache*,struct page*) ; 
 int /*<<< orphan*/  kmem_rcu_free ; 
 int /*<<< orphan*/  slab_destroy_debugcheck (struct kmem_cache*,struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void slab_destroy(struct kmem_cache *cachep, struct page *page)
{
	void *freelist;

	freelist = page->freelist;
	slab_destroy_debugcheck(cachep, page);
	if (unlikely(cachep->flags & SLAB_TYPESAFE_BY_RCU))
		call_rcu(&page->rcu_head, kmem_rcu_free);
	else
		kmem_freepages(cachep, page);

	/*
	 * From now on, we don't use freelist
	 * although actual page can be freed in rcu context
	 */
	if (OFF_SLAB(cachep))
		kmem_cache_free(cachep->freelist_cache, freelist);
}