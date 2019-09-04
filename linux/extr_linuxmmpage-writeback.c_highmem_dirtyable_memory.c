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

__attribute__((used)) static unsigned long highmem_dirtyable_memory(unsigned long total)
{
#ifdef CONFIG_HIGHMEM
	int node;
	unsigned long x = 0;
	int i;

	for_each_node_state(node, N_HIGH_MEMORY) {
		for (i = ZONE_NORMAL + 1; i < MAX_NR_ZONES; i++) {
			struct zone *z;
			unsigned long nr_pages;

			if (!is_highmem_idx(i))
				continue;

			z = &NODE_DATA(node)->node_zones[i];
			if (!populated_zone(z))
				continue;

			nr_pages = zone_page_state(z, NR_FREE_PAGES);
			/* watch for underflows */
			nr_pages -= min(nr_pages, high_wmark_pages(z));
			nr_pages += zone_page_state(z, NR_ZONE_INACTIVE_FILE);
			nr_pages += zone_page_state(z, NR_ZONE_ACTIVE_FILE);
			x += nr_pages;
		}
	}

	/*
	 * Unreclaimable memory (kernel memory or anonymous memory
	 * without swap) can bring down the dirtyable pages below
	 * the zone's dirty balance reserve and the above calculation
	 * will underflow.  However we still want to add in nodes
	 * which are below threshold (negative values) to get a more
	 * accurate calculation but make sure that the total never
	 * underflows.
	 */
	if ((long)x < 0)
		x = 0;

	/*
	 * Make sure that the number of highmem pages is never larger
	 * than the number of the total dirtyable memory. This can only
	 * occur in very strange VM situations but we want to make sure
	 * that this does not occur.
	 */
	return min(x, total);
#else
	return 0;
#endif
}