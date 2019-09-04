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
 int MIGRATE_RECLAIMABLE ; 
 int MIGRATE_UNMOVABLE ; 
 scalar_t__ page_group_by_mobility_disabled ; 
 unsigned int pageblock_order ; 

__attribute__((used)) static bool can_steal_fallback(unsigned int order, int start_mt)
{
	/*
	 * Leaving this order check is intended, although there is
	 * relaxed order check in next check. The reason is that
	 * we can actually steal whole pageblock if this condition met,
	 * but, below check doesn't guarantee it and that is just heuristic
	 * so could be changed anytime.
	 */
	if (order >= pageblock_order)
		return true;

	if (order >= pageblock_order / 2 ||
		start_mt == MIGRATE_RECLAIMABLE ||
		start_mt == MIGRATE_UNMOVABLE ||
		page_group_by_mobility_disabled)
		return true;

	return false;
}