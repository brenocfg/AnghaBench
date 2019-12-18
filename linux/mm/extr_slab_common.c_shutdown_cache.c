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
struct kmem_cache {int flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EBUSY ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 scalar_t__ __kmem_cache_shutdown (struct kmem_cache*) ; 
 int /*<<< orphan*/  kasan_cache_shutdown (struct kmem_cache*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcg_unlink_cache (struct kmem_cache*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slab_caches_to_rcu_destroy ; 
 int /*<<< orphan*/  slab_caches_to_rcu_destroy_work ; 
 int /*<<< orphan*/  slab_kmem_cache_release (struct kmem_cache*) ; 
 int /*<<< orphan*/  sysfs_slab_release (struct kmem_cache*) ; 
 int /*<<< orphan*/  sysfs_slab_unlink (struct kmem_cache*) ; 

__attribute__((used)) static int shutdown_cache(struct kmem_cache *s)
{
	/* free asan quarantined objects */
	kasan_cache_shutdown(s);

	if (__kmem_cache_shutdown(s) != 0)
		return -EBUSY;

	memcg_unlink_cache(s);
	list_del(&s->list);

	if (s->flags & SLAB_TYPESAFE_BY_RCU) {
#ifdef SLAB_SUPPORTS_SYSFS
		sysfs_slab_unlink(s);
#endif
		list_add_tail(&s->list, &slab_caches_to_rcu_destroy);
		schedule_work(&slab_caches_to_rcu_destroy_work);
	} else {
#ifdef SLAB_SUPPORTS_SYSFS
		sysfs_slab_unlink(s);
		sysfs_slab_release(s);
#else
		slab_kmem_cache_release(s);
#endif
	}

	return 0;
}