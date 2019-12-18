#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zone {TYPE_1__* zone_pgdat; } ;
struct TYPE_5__ {scalar_t__ kswapd_classzone_idx; int kswapd_order; scalar_t__ kswapd_failures; int /*<<< orphan*/  kswapd_wait; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_1__ pg_data_t ;
typedef  int gfp_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 scalar_t__ MAX_NR_ZONES ; 
 scalar_t__ MAX_RECLAIM_RETRIES ; 
 int __GFP_DIRECT_RECLAIM ; 
 int /*<<< orphan*/  cpuset_zone_allowed (struct zone*,int) ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 void* max (int,int) ; 
 scalar_t__ pgdat_balanced (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pgdat_watermark_boosted (TYPE_1__*,int) ; 
 int /*<<< orphan*/  trace_mm_vmscan_wakeup_kswapd (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_kcompactd (TYPE_1__*,int,int) ; 

void wakeup_kswapd(struct zone *zone, gfp_t gfp_flags, int order,
		   enum zone_type classzone_idx)
{
	pg_data_t *pgdat;

	if (!managed_zone(zone))
		return;

	if (!cpuset_zone_allowed(zone, gfp_flags))
		return;
	pgdat = zone->zone_pgdat;

	if (pgdat->kswapd_classzone_idx == MAX_NR_ZONES)
		pgdat->kswapd_classzone_idx = classzone_idx;
	else
		pgdat->kswapd_classzone_idx = max(pgdat->kswapd_classzone_idx,
						  classzone_idx);
	pgdat->kswapd_order = max(pgdat->kswapd_order, order);
	if (!waitqueue_active(&pgdat->kswapd_wait))
		return;

	/* Hopeless node, leave it to direct reclaim if possible */
	if (pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES ||
	    (pgdat_balanced(pgdat, order, classzone_idx) &&
	     !pgdat_watermark_boosted(pgdat, classzone_idx))) {
		/*
		 * There may be plenty of free memory available, but it's too
		 * fragmented for high-order allocations.  Wake up kcompactd
		 * and rely on compaction_suitable() to determine if it's
		 * needed.  If it fails, it will defer subsequent attempts to
		 * ratelimit its work.
		 */
		if (!(gfp_flags & __GFP_DIRECT_RECLAIM))
			wakeup_kcompactd(pgdat, order, classzone_idx);
		return;
	}

	trace_mm_vmscan_wakeup_kswapd(pgdat->node_id, classzone_idx, order,
				      gfp_flags);
	wake_up_interruptible(&pgdat->kswapd_wait);
}