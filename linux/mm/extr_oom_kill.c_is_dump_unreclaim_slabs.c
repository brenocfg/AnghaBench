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
 int /*<<< orphan*/  NR_ACTIVE_ANON ; 
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int /*<<< orphan*/  NR_ISOLATED_ANON ; 
 int /*<<< orphan*/  NR_ISOLATED_FILE ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int /*<<< orphan*/  NR_UNEVICTABLE ; 
 unsigned long global_node_page_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_dump_unreclaim_slabs(void)
{
	unsigned long nr_lru;

	nr_lru = global_node_page_state(NR_ACTIVE_ANON) +
		 global_node_page_state(NR_INACTIVE_ANON) +
		 global_node_page_state(NR_ACTIVE_FILE) +
		 global_node_page_state(NR_INACTIVE_FILE) +
		 global_node_page_state(NR_ISOLATED_ANON) +
		 global_node_page_state(NR_ISOLATED_FILE) +
		 global_node_page_state(NR_UNEVICTABLE);

	return (global_node_page_state(NR_SLAB_UNRECLAIMABLE) > nr_lru);
}