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
struct ecryptfs_cache_info {int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ecryptfs_cache_info*) ; 
 struct ecryptfs_cache_info* ecryptfs_cache_infos ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static void ecryptfs_free_kmem_caches(void)
{
	int i;

	/*
	 * Make sure all delayed rcu free inodes are flushed before we
	 * destroy cache.
	 */
	rcu_barrier();

	for (i = 0; i < ARRAY_SIZE(ecryptfs_cache_infos); i++) {
		struct ecryptfs_cache_info *info;

		info = &ecryptfs_cache_infos[i];
		kmem_cache_destroy(*(info->cache));
	}
}