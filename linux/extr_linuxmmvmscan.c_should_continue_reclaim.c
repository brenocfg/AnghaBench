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
struct scan_control {int gfp_mask; unsigned long nr_reclaimed; int reclaim_idx; int /*<<< orphan*/  order; } ;
struct pglist_data {struct zone* node_zones; } ;

/* Variables and functions */
#define  COMPACT_CONTINUE 129 
#define  COMPACT_SUCCESS 128 
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int __GFP_RETRY_MAYFAIL ; 
 unsigned long compact_gap (int /*<<< orphan*/ ) ; 
 int compaction_suitable (struct zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_nr_swap_pages () ; 
 int /*<<< orphan*/  in_reclaim_compaction (struct scan_control*) ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 unsigned long node_page_state (struct pglist_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool should_continue_reclaim(struct pglist_data *pgdat,
					unsigned long nr_reclaimed,
					unsigned long nr_scanned,
					struct scan_control *sc)
{
	unsigned long pages_for_compaction;
	unsigned long inactive_lru_pages;
	int z;

	/* If not in reclaim/compaction mode, stop */
	if (!in_reclaim_compaction(sc))
		return false;

	/* Consider stopping depending on scan and reclaim activity */
	if (sc->gfp_mask & __GFP_RETRY_MAYFAIL) {
		/*
		 * For __GFP_RETRY_MAYFAIL allocations, stop reclaiming if the
		 * full LRU list has been scanned and we are still failing
		 * to reclaim pages. This full LRU scan is potentially
		 * expensive but a __GFP_RETRY_MAYFAIL caller really wants to succeed
		 */
		if (!nr_reclaimed && !nr_scanned)
			return false;
	} else {
		/*
		 * For non-__GFP_RETRY_MAYFAIL allocations which can presumably
		 * fail without consequence, stop if we failed to reclaim
		 * any pages from the last SWAP_CLUSTER_MAX number of
		 * pages that were scanned. This will return to the
		 * caller faster at the risk reclaim/compaction and
		 * the resulting allocation attempt fails
		 */
		if (!nr_reclaimed)
			return false;
	}

	/*
	 * If we have not reclaimed enough pages for compaction and the
	 * inactive lists are large enough, continue reclaiming
	 */
	pages_for_compaction = compact_gap(sc->order);
	inactive_lru_pages = node_page_state(pgdat, NR_INACTIVE_FILE);
	if (get_nr_swap_pages() > 0)
		inactive_lru_pages += node_page_state(pgdat, NR_INACTIVE_ANON);
	if (sc->nr_reclaimed < pages_for_compaction &&
			inactive_lru_pages > pages_for_compaction)
		return true;

	/* If compaction would go ahead or the allocation would succeed, stop */
	for (z = 0; z <= sc->reclaim_idx; z++) {
		struct zone *zone = &pgdat->node_zones[z];
		if (!managed_zone(zone))
			continue;

		switch (compaction_suitable(zone, sc->order, 0, sc->reclaim_idx)) {
		case COMPACT_SUCCESS:
		case COMPACT_CONTINUE:
			return false;
		default:
			/* check next zone */
			;
		}
	}
	return true;
}