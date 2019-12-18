#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zone {int dummy; } ;
struct lruvec {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;
struct TYPE_3__ {struct zone* node_zones; } ;

/* Variables and functions */
 int MAX_NR_ZONES ; 
 int NR_LRU_BASE ; 
 int NR_ZONE_LRU_BASE ; 
 TYPE_1__* lruvec_pgdat (struct lruvec*) ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 int /*<<< orphan*/  mem_cgroup_disabled () ; 
 unsigned long mem_cgroup_get_zone_lru_size (struct lruvec*,int,int) ; 
 scalar_t__ min (unsigned long,unsigned long) ; 
 unsigned long node_page_state (TYPE_1__*,int) ; 
 unsigned long zone_page_state (struct zone*,int) ; 

unsigned long lruvec_lru_size(struct lruvec *lruvec, enum lru_list lru, int zone_idx)
{
	unsigned long lru_size = 0;
	int zid;

	if (!mem_cgroup_disabled()) {
		for (zid = 0; zid < MAX_NR_ZONES; zid++)
			lru_size += mem_cgroup_get_zone_lru_size(lruvec, lru, zid);
	} else
		lru_size = node_page_state(lruvec_pgdat(lruvec), NR_LRU_BASE + lru);

	for (zid = zone_idx + 1; zid < MAX_NR_ZONES; zid++) {
		struct zone *zone = &lruvec_pgdat(lruvec)->node_zones[zid];
		unsigned long size;

		if (!managed_zone(zone))
			continue;

		if (!mem_cgroup_disabled())
			size = mem_cgroup_get_zone_lru_size(lruvec, lru, zid);
		else
			size = zone_page_state(&lruvec_pgdat(lruvec)->node_zones[zid],
				       NR_ZONE_LRU_BASE + lru);
		lru_size -= min(size, lru_size);
	}

	return lru_size;

}