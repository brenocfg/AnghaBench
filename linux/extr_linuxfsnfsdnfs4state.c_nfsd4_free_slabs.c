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
 int /*<<< orphan*/  client_slab ; 
 int /*<<< orphan*/  deleg_slab ; 
 int /*<<< orphan*/  file_slab ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockowner_slab ; 
 int /*<<< orphan*/  odstate_slab ; 
 int /*<<< orphan*/  openowner_slab ; 
 int /*<<< orphan*/  stateid_slab ; 

void
nfsd4_free_slabs(void)
{
	kmem_cache_destroy(client_slab);
	kmem_cache_destroy(openowner_slab);
	kmem_cache_destroy(lockowner_slab);
	kmem_cache_destroy(file_slab);
	kmem_cache_destroy(stateid_slab);
	kmem_cache_destroy(deleg_slab);
	kmem_cache_destroy(odstate_slab);
}