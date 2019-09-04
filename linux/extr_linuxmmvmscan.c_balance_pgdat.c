#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct zone {int dummy; } ;
struct scan_control {int order; int priority; int may_writepage; int may_unmap; int may_swap; unsigned long nr_reclaimed; int reclaim_idx; int /*<<< orphan*/  gfp_mask; scalar_t__ nr_scanned; } ;
struct TYPE_9__ {int /*<<< orphan*/  kswapd_failures; int /*<<< orphan*/  pfmemalloc_wait; struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int DEF_PRIORITY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_NR_ZONES ; 
 int /*<<< orphan*/  PAGEOUTRUN ; 
 int /*<<< orphan*/  __fs_reclaim_acquire () ; 
 int /*<<< orphan*/  __fs_reclaim_release () ; 
 int /*<<< orphan*/  age_active_anon (TYPE_1__*,struct scan_control*) ; 
 scalar_t__ allow_direct_reclaim (TYPE_1__*) ; 
 scalar_t__ buffer_heads_over_limit ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 scalar_t__ kswapd_shrink_node (TYPE_1__*,struct scan_control*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  managed_zone (struct zone*) ; 
 unsigned long mem_cgroup_soft_limit_reclaim (TYPE_1__*,int,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ pgdat_balanced (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  snapshot_refaults (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int try_to_freeze () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int balance_pgdat(pg_data_t *pgdat, int order, int classzone_idx)
{
	int i;
	unsigned long nr_soft_reclaimed;
	unsigned long nr_soft_scanned;
	struct zone *zone;
	struct scan_control sc = {
		.gfp_mask = GFP_KERNEL,
		.order = order,
		.priority = DEF_PRIORITY,
		.may_writepage = !laptop_mode,
		.may_unmap = 1,
		.may_swap = 1,
	};

	__fs_reclaim_acquire();

	count_vm_event(PAGEOUTRUN);

	do {
		unsigned long nr_reclaimed = sc.nr_reclaimed;
		bool raise_priority = true;
		bool ret;

		sc.reclaim_idx = classzone_idx;

		/*
		 * If the number of buffer_heads exceeds the maximum allowed
		 * then consider reclaiming from all zones. This has a dual
		 * purpose -- on 64-bit systems it is expected that
		 * buffer_heads are stripped during active rotation. On 32-bit
		 * systems, highmem pages can pin lowmem memory and shrinking
		 * buffers can relieve lowmem pressure. Reclaim may still not
		 * go ahead if all eligible zones for the original allocation
		 * request are balanced to avoid excessive reclaim from kswapd.
		 */
		if (buffer_heads_over_limit) {
			for (i = MAX_NR_ZONES - 1; i >= 0; i--) {
				zone = pgdat->node_zones + i;
				if (!managed_zone(zone))
					continue;

				sc.reclaim_idx = i;
				break;
			}
		}

		/*
		 * Only reclaim if there are no eligible zones. Note that
		 * sc.reclaim_idx is not used as buffer_heads_over_limit may
		 * have adjusted it.
		 */
		if (pgdat_balanced(pgdat, sc.order, classzone_idx))
			goto out;

		/*
		 * Do some background aging of the anon list, to give
		 * pages a chance to be referenced before reclaiming. All
		 * pages are rotated regardless of classzone as this is
		 * about consistent aging.
		 */
		age_active_anon(pgdat, &sc);

		/*
		 * If we're getting trouble reclaiming, start doing writepage
		 * even in laptop mode.
		 */
		if (sc.priority < DEF_PRIORITY - 2)
			sc.may_writepage = 1;

		/* Call soft limit reclaim before calling shrink_node. */
		sc.nr_scanned = 0;
		nr_soft_scanned = 0;
		nr_soft_reclaimed = mem_cgroup_soft_limit_reclaim(pgdat, sc.order,
						sc.gfp_mask, &nr_soft_scanned);
		sc.nr_reclaimed += nr_soft_reclaimed;

		/*
		 * There should be no need to raise the scanning priority if
		 * enough pages are already being scanned that that high
		 * watermark would be met at 100% efficiency.
		 */
		if (kswapd_shrink_node(pgdat, &sc))
			raise_priority = false;

		/*
		 * If the low watermark is met there is no need for processes
		 * to be throttled on pfmemalloc_wait as they should not be
		 * able to safely make forward progress. Wake them
		 */
		if (waitqueue_active(&pgdat->pfmemalloc_wait) &&
				allow_direct_reclaim(pgdat))
			wake_up_all(&pgdat->pfmemalloc_wait);

		/* Check if kswapd should be suspending */
		__fs_reclaim_release();
		ret = try_to_freeze();
		__fs_reclaim_acquire();
		if (ret || kthread_should_stop())
			break;

		/*
		 * Raise priority if scanning rate is too low or there was no
		 * progress in reclaiming pages
		 */
		nr_reclaimed = sc.nr_reclaimed - nr_reclaimed;
		if (raise_priority || !nr_reclaimed)
			sc.priority--;
	} while (sc.priority >= 1);

	if (!sc.nr_reclaimed)
		pgdat->kswapd_failures++;

out:
	snapshot_refaults(NULL, pgdat);
	__fs_reclaim_release();
	/*
	 * Return the order kswapd stopped reclaiming at as
	 * prepare_kswapd_sleep() takes it into account. If another caller
	 * entered the allocator slow path while kswapd was awake, order will
	 * remain at the higher level.
	 */
	return sc.order;
}