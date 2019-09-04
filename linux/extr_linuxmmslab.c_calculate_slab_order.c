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
struct kmem_cache {int size; unsigned int num; int gfporder; } ;
typedef  int slab_flags_t ;
typedef  int /*<<< orphan*/  freelist_idx_t ;

/* Variables and functions */
 int CFLGS_OFF_SLAB ; 
 int KMALLOC_MAX_ORDER ; 
 scalar_t__ OFF_SLAB (struct kmem_cache*) ; 
 int PAGE_SIZE ; 
 unsigned int SLAB_OBJ_MAX_NUM ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 unsigned int cache_estimate (int,size_t,int,size_t*) ; 
 struct kmem_cache* kmalloc_slab (size_t,unsigned int) ; 
 int slab_max_order ; 

__attribute__((used)) static size_t calculate_slab_order(struct kmem_cache *cachep,
				size_t size, slab_flags_t flags)
{
	size_t left_over = 0;
	int gfporder;

	for (gfporder = 0; gfporder <= KMALLOC_MAX_ORDER; gfporder++) {
		unsigned int num;
		size_t remainder;

		num = cache_estimate(gfporder, size, flags, &remainder);
		if (!num)
			continue;

		/* Can't handle number of objects more than SLAB_OBJ_MAX_NUM */
		if (num > SLAB_OBJ_MAX_NUM)
			break;

		if (flags & CFLGS_OFF_SLAB) {
			struct kmem_cache *freelist_cache;
			size_t freelist_size;

			freelist_size = num * sizeof(freelist_idx_t);
			freelist_cache = kmalloc_slab(freelist_size, 0u);
			if (!freelist_cache)
				continue;

			/*
			 * Needed to avoid possible looping condition
			 * in cache_grow_begin()
			 */
			if (OFF_SLAB(freelist_cache))
				continue;

			/* check if off slab has enough benefit */
			if (freelist_cache->size > cachep->size / 2)
				continue;
		}

		/* Found something acceptable - save it away */
		cachep->num = num;
		cachep->gfporder = gfporder;
		left_over = remainder;

		/*
		 * A VFS-reclaimable slab tends to have most allocations
		 * as GFP_NOFS and we really don't want to have to be allocating
		 * higher-order pages when we are unable to shrink dcache.
		 */
		if (flags & SLAB_RECLAIM_ACCOUNT)
			break;

		/*
		 * Large number of objects is good, but very large slabs are
		 * currently bad for the gfp()s.
		 */
		if (gfporder >= slab_max_order)
			break;

		/*
		 * Acceptable internal fragmentation?
		 */
		if (left_over * 8 <= (PAGE_SIZE << gfporder))
			break;
	}
	return left_over;
}