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
 int /*<<< orphan*/ * dlm_lockname_cache ; 
 int /*<<< orphan*/ * dlm_lockres_cache ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

void dlm_destroy_master_caches(void)
{
	kmem_cache_destroy(dlm_lockname_cache);
	dlm_lockname_cache = NULL;

	kmem_cache_destroy(dlm_lockres_cache);
	dlm_lockres_cache = NULL;
}