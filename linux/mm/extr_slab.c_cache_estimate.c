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
typedef  int slab_flags_t ;
typedef  int /*<<< orphan*/  freelist_idx_t ;

/* Variables and functions */
 int CFLGS_OBJFREELIST_SLAB ; 
 int CFLGS_OFF_SLAB ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static unsigned int cache_estimate(unsigned long gfporder, size_t buffer_size,
		slab_flags_t flags, size_t *left_over)
{
	unsigned int num;
	size_t slab_size = PAGE_SIZE << gfporder;

	/*
	 * The slab management structure can be either off the slab or
	 * on it. For the latter case, the memory allocated for a
	 * slab is used for:
	 *
	 * - @buffer_size bytes for each object
	 * - One freelist_idx_t for each object
	 *
	 * We don't need to consider alignment of freelist because
	 * freelist will be at the end of slab page. The objects will be
	 * at the correct alignment.
	 *
	 * If the slab management structure is off the slab, then the
	 * alignment will already be calculated into the size. Because
	 * the slabs are all pages aligned, the objects will be at the
	 * correct alignment when allocated.
	 */
	if (flags & (CFLGS_OBJFREELIST_SLAB | CFLGS_OFF_SLAB)) {
		num = slab_size / buffer_size;
		*left_over = slab_size % buffer_size;
	} else {
		num = slab_size / (buffer_size + sizeof(freelist_idx_t));
		*left_over = slab_size %
			(buffer_size + sizeof(freelist_idx_t));
	}

	return num;
}