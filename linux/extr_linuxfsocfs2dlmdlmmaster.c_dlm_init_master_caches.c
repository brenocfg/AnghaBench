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
struct dlm_lock_resource {int dummy; } ;

/* Variables and functions */
 int DLM_LOCKID_NAME_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  dlm_destroy_master_caches () ; 
 void* dlm_lockname_cache ; 
 void* dlm_lockres_cache ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dlm_init_master_caches(void)
{
	dlm_lockres_cache = kmem_cache_create("o2dlm_lockres",
					      sizeof(struct dlm_lock_resource),
					      0, SLAB_HWCACHE_ALIGN, NULL);
	if (!dlm_lockres_cache)
		goto bail;

	dlm_lockname_cache = kmem_cache_create("o2dlm_lockname",
					       DLM_LOCKID_NAME_MAX, 0,
					       SLAB_HWCACHE_ALIGN, NULL);
	if (!dlm_lockname_cache)
		goto bail;

	return 0;
bail:
	dlm_destroy_master_caches();
	return -ENOMEM;
}