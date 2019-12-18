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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ DMA_DEBUG_DYNAMIC_ENTRIES ; 
 scalar_t__ nr_prealloc_entries ; 
 scalar_t__ nr_total_entries ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__) ; 

void __dma_entry_alloc_check_leak(void)
{
	u32 tmp = nr_total_entries % nr_prealloc_entries;

	/* Shout each time we tick over some multiple of the initial pool */
	if (tmp < DMA_DEBUG_DYNAMIC_ENTRIES) {
		pr_info("dma_debug_entry pool grown to %u (%u00%%)\n",
			nr_total_entries,
			(nr_total_entries / nr_prealloc_entries));
	}
}