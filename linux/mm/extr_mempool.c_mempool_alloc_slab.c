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
struct kmem_cache {int /*<<< orphan*/  ctor; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 void* kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 

void *mempool_alloc_slab(gfp_t gfp_mask, void *pool_data)
{
	struct kmem_cache *mem = pool_data;
	VM_BUG_ON(mem->ctor);
	return kmem_cache_alloc(mem, gfp_mask);
}