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
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 scalar_t__ global_node_page_state (int /*<<< orphan*/ ) ; 
 unsigned long global_zone_page_state (int /*<<< orphan*/ ) ; 
 scalar_t__ highmem_dirtyable_memory (unsigned long) ; 
 scalar_t__ min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  totalreserve_pages ; 
 int /*<<< orphan*/  vm_highmem_is_dirtyable ; 

__attribute__((used)) static unsigned long global_dirtyable_memory(void)
{
	unsigned long x;

	x = global_zone_page_state(NR_FREE_PAGES);
	/*
	 * Pages reserved for the kernel should not be considered
	 * dirtyable, to prevent a situation where reclaim has to
	 * clean pages in order to balance the zones.
	 */
	x -= min(x, totalreserve_pages);

	x += global_node_page_state(NR_INACTIVE_FILE);
	x += global_node_page_state(NR_ACTIVE_FILE);

	if (!vm_highmem_is_dirtyable)
		x -= highmem_dirtyable_memory(x);

	return x + 1;	/* Ensure that we never return 0 */
}