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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  Z_EROFS_WORKGROUP_SIZE ; 
 int /*<<< orphan*/  init_unzip_workqueue () ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * z_erofs_workgroup_cachep ; 

int z_erofs_init_zip_subsystem(void)
{
	z_erofs_workgroup_cachep =
		kmem_cache_create("erofs_compress",
		Z_EROFS_WORKGROUP_SIZE, 0,
		SLAB_RECLAIM_ACCOUNT, NULL);

	if (z_erofs_workgroup_cachep != NULL) {
		if (!init_unzip_workqueue())
			return 0;

		kmem_cache_destroy(z_erofs_workgroup_cachep);
	}
	return -ENOMEM;
}