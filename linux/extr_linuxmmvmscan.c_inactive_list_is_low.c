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
struct scan_control {int /*<<< orphan*/  reclaim_idx; } ;
struct pglist_data {int /*<<< orphan*/  node_id; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {unsigned long refaults; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int LRU_ACTIVE ; 
 int LRU_FILE ; 
 int /*<<< orphan*/  MAX_NR_ZONES ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WORKINGSET_ACTIVATE ; 
 unsigned long int_sqrt (int) ; 
 unsigned long lruvec_lru_size (struct lruvec*,int,int /*<<< orphan*/ ) ; 
 struct pglist_data* lruvec_pgdat (struct lruvec*) ; 
 unsigned long memcg_page_state (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 unsigned long node_page_state (struct pglist_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_swap_pages ; 
 int /*<<< orphan*/  trace_mm_vmscan_inactive_list_is_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,int) ; 

__attribute__((used)) static bool inactive_list_is_low(struct lruvec *lruvec, bool file,
				 struct mem_cgroup *memcg,
				 struct scan_control *sc, bool actual_reclaim)
{
	enum lru_list active_lru = file * LRU_FILE + LRU_ACTIVE;
	struct pglist_data *pgdat = lruvec_pgdat(lruvec);
	enum lru_list inactive_lru = file * LRU_FILE;
	unsigned long inactive, active;
	unsigned long inactive_ratio;
	unsigned long refaults;
	unsigned long gb;

	/*
	 * If we don't have swap space, anonymous page deactivation
	 * is pointless.
	 */
	if (!file && !total_swap_pages)
		return false;

	inactive = lruvec_lru_size(lruvec, inactive_lru, sc->reclaim_idx);
	active = lruvec_lru_size(lruvec, active_lru, sc->reclaim_idx);

	if (memcg)
		refaults = memcg_page_state(memcg, WORKINGSET_ACTIVATE);
	else
		refaults = node_page_state(pgdat, WORKINGSET_ACTIVATE);

	/*
	 * When refaults are being observed, it means a new workingset
	 * is being established. Disable active list protection to get
	 * rid of the stale workingset quickly.
	 */
	if (file && actual_reclaim && lruvec->refaults != refaults) {
		inactive_ratio = 0;
	} else {
		gb = (inactive + active) >> (30 - PAGE_SHIFT);
		if (gb)
			inactive_ratio = int_sqrt(10 * gb);
		else
			inactive_ratio = 1;
	}

	if (actual_reclaim)
		trace_mm_vmscan_inactive_list_is_low(pgdat->node_id, sc->reclaim_idx,
			lruvec_lru_size(lruvec, inactive_lru, MAX_NR_ZONES), inactive,
			lruvec_lru_size(lruvec, active_lru, MAX_NR_ZONES), active,
			inactive_ratio, file);

	return inactive * inactive_ratio < active;
}