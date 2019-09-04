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
struct TYPE_3__ {scalar_t__ kswapd_failures; int /*<<< orphan*/  kswapd_wait; int /*<<< orphan*/  kswapd_classzone_idx; struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 scalar_t__ MAX_RECLAIM_RETRIES ; 
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int ZONE_NORMAL ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ min_wmark_pages (struct zone*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_reclaimable_pages (struct zone*) ; 

__attribute__((used)) static bool allow_direct_reclaim(pg_data_t *pgdat)
{
	struct zone *zone;
	unsigned long pfmemalloc_reserve = 0;
	unsigned long free_pages = 0;
	int i;
	bool wmark_ok;

	if (pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES)
		return true;

	for (i = 0; i <= ZONE_NORMAL; i++) {
		zone = &pgdat->node_zones[i];
		if (!managed_zone(zone))
			continue;

		if (!zone_reclaimable_pages(zone))
			continue;

		pfmemalloc_reserve += min_wmark_pages(zone);
		free_pages += zone_page_state(zone, NR_FREE_PAGES);
	}

	/* If there are no reserves (unexpected config) then do not throttle */
	if (!pfmemalloc_reserve)
		return true;

	wmark_ok = free_pages > pfmemalloc_reserve / 2;

	/* kswapd must be awake if processes are being throttled */
	if (!wmark_ok && waitqueue_active(&pgdat->kswapd_wait)) {
		pgdat->kswapd_classzone_idx = min(pgdat->kswapd_classzone_idx,
						(enum zone_type)ZONE_NORMAL);
		wake_up_interruptible(&pgdat->kswapd_wait);
	}

	return wmark_ok;
}