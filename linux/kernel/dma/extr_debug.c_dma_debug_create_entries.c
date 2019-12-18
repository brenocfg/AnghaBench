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
struct dma_debug_entry {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int DMA_DEBUG_DYNAMIC_ENTRIES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free_entries ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nr_total_entries ; 
 int num_free_entries ; 

__attribute__((used)) static int dma_debug_create_entries(gfp_t gfp)
{
	struct dma_debug_entry *entry;
	int i;

	entry = (void *)get_zeroed_page(gfp);
	if (!entry)
		return -ENOMEM;

	for (i = 0; i < DMA_DEBUG_DYNAMIC_ENTRIES; i++)
		list_add_tail(&entry[i].list, &free_entries);

	num_free_entries += DMA_DEBUG_DYNAMIC_ENTRIES;
	nr_total_entries += DMA_DEBUG_DYNAMIC_ENTRIES;

	return 0;
}