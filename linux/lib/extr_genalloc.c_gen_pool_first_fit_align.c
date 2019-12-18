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
struct genpool_data_align {unsigned long align; } ;
struct gen_pool {int min_alloc_order; } ;

/* Variables and functions */
 unsigned long bitmap_find_next_zero_area_off (unsigned long*,unsigned long,unsigned long,unsigned int,unsigned long,unsigned long) ; 

unsigned long gen_pool_first_fit_align(unsigned long *map, unsigned long size,
		unsigned long start, unsigned int nr, void *data,
		struct gen_pool *pool, unsigned long start_addr)
{
	struct genpool_data_align *alignment;
	unsigned long align_mask, align_off;
	int order;

	alignment = data;
	order = pool->min_alloc_order;
	align_mask = ((alignment->align + (1UL << order) - 1) >> order) - 1;
	align_off = (start_addr & (alignment->align - 1)) >> order;

	return bitmap_find_next_zero_area_off(map, size, start, nr,
					      align_mask, align_off);
}