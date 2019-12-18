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
struct cma {unsigned long base_pfn; unsigned long order_per_bit; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long cma_bitmap_aligned_offset(const struct cma *cma,
					       unsigned int align_order)
{
	return (cma->base_pfn & ((1UL << align_order) - 1))
		>> cma->order_per_bit;
}