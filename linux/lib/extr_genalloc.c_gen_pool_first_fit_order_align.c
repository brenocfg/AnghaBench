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
struct gen_pool {int dummy; } ;

/* Variables and functions */
 unsigned long bitmap_find_next_zero_area (unsigned long*,unsigned long,unsigned long,unsigned int,unsigned long) ; 
 int roundup_pow_of_two (unsigned int) ; 

unsigned long gen_pool_first_fit_order_align(unsigned long *map,
		unsigned long size, unsigned long start,
		unsigned int nr, void *data, struct gen_pool *pool,
		unsigned long start_addr)
{
	unsigned long align_mask = roundup_pow_of_two(nr) - 1;

	return bitmap_find_next_zero_area(map, size, start, nr, align_mask);
}