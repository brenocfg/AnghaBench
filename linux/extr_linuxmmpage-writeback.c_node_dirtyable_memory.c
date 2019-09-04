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
struct zone {int dummy; } ;
struct pglist_data {int /*<<< orphan*/  totalreserve_pages; struct zone* node_zones; } ;

/* Variables and functions */
 int MAX_NR_ZONES ; 
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 scalar_t__ min (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ node_page_state (struct pglist_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 scalar_t__ zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long node_dirtyable_memory(struct pglist_data *pgdat)
{
	unsigned long nr_pages = 0;
	int z;

	for (z = 0; z < MAX_NR_ZONES; z++) {
		struct zone *zone = pgdat->node_zones + z;

		if (!populated_zone(zone))
			continue;

		nr_pages += zone_page_state(zone, NR_FREE_PAGES);
	}

	/*
	 * Pages reserved for the kernel should not be considered
	 * dirtyable, to prevent a situation where reclaim has to
	 * clean pages in order to balance the zones.
	 */
	nr_pages -= min(nr_pages, pgdat->totalreserve_pages);

	nr_pages += node_page_state(pgdat, NR_INACTIVE_FILE);
	nr_pages += node_page_state(pgdat, NR_ACTIVE_FILE);

	return nr_pages;
}