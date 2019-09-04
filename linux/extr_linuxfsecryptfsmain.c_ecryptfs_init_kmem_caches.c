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
struct ecryptfs_cache_info {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * cache; int /*<<< orphan*/  ctor; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ecryptfs_cache_info*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SLAB_HWCACHE_ALIGN ; 
 struct ecryptfs_cache_info* ecryptfs_cache_infos ; 
 int /*<<< orphan*/  ecryptfs_free_kmem_caches () ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_init_kmem_caches(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ecryptfs_cache_infos); i++) {
		struct ecryptfs_cache_info *info;

		info = &ecryptfs_cache_infos[i];
		*(info->cache) = kmem_cache_create(info->name, info->size, 0,
				SLAB_HWCACHE_ALIGN | info->flags, info->ctor);
		if (!*(info->cache)) {
			ecryptfs_free_kmem_caches();
			ecryptfs_printk(KERN_WARNING, "%s: "
					"kmem_cache_create failed\n",
					info->name);
			return -ENOMEM;
		}
	}
	return 0;
}