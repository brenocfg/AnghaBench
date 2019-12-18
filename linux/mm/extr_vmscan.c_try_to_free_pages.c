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
struct zonelist {int dummy; } ;
struct scan_control {int order; scalar_t__ priority; int may_writepage; int may_unmap; int may_swap; int /*<<< orphan*/  gfp_mask; int /*<<< orphan*/  reclaim_state; int /*<<< orphan*/ * nodemask; int /*<<< orphan*/  reclaim_idx; int /*<<< orphan*/  nr_to_reclaim; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ DEF_PRIORITY ; 
 scalar_t__ MAX_NR_ZONES ; 
 scalar_t__ MAX_ORDER ; 
 scalar_t__ S8_MAX ; 
 int /*<<< orphan*/  SWAP_CLUSTER_MAX ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_gfp_context (int /*<<< orphan*/ ) ; 
 unsigned long do_try_to_free_pages (struct zonelist*,struct scan_control*) ; 
 int /*<<< orphan*/  gfp_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  set_task_reclaim_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ throttle_direct_reclaim (int /*<<< orphan*/ ,struct zonelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_vmscan_direct_reclaim_begin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mm_vmscan_direct_reclaim_end (unsigned long) ; 

unsigned long try_to_free_pages(struct zonelist *zonelist, int order,
				gfp_t gfp_mask, nodemask_t *nodemask)
{
	unsigned long nr_reclaimed;
	struct scan_control sc = {
		.nr_to_reclaim = SWAP_CLUSTER_MAX,
		.gfp_mask = current_gfp_context(gfp_mask),
		.reclaim_idx = gfp_zone(gfp_mask),
		.order = order,
		.nodemask = nodemask,
		.priority = DEF_PRIORITY,
		.may_writepage = !laptop_mode,
		.may_unmap = 1,
		.may_swap = 1,
	};

	/*
	 * scan_control uses s8 fields for order, priority, and reclaim_idx.
	 * Confirm they are large enough for max values.
	 */
	BUILD_BUG_ON(MAX_ORDER > S8_MAX);
	BUILD_BUG_ON(DEF_PRIORITY > S8_MAX);
	BUILD_BUG_ON(MAX_NR_ZONES > S8_MAX);

	/*
	 * Do not enter reclaim if fatal signal was delivered while throttled.
	 * 1 is returned so that the page allocator does not OOM kill at this
	 * point.
	 */
	if (throttle_direct_reclaim(sc.gfp_mask, zonelist, nodemask))
		return 1;

	set_task_reclaim_state(current, &sc.reclaim_state);
	trace_mm_vmscan_direct_reclaim_begin(order, sc.gfp_mask);

	nr_reclaimed = do_try_to_free_pages(zonelist, &sc);

	trace_mm_vmscan_direct_reclaim_end(nr_reclaimed);
	set_task_reclaim_state(current, NULL);

	return nr_reclaimed;
}