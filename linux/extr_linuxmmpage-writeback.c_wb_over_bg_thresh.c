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
struct dirty_throttle_control {scalar_t__ dirty; scalar_t__ bg_thresh; int /*<<< orphan*/  wb; int /*<<< orphan*/  avail; int /*<<< orphan*/  member_0; } ;
struct bdi_writeback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDTC_INIT (struct bdi_writeback*) ; 
 int /*<<< orphan*/  MDTC_INIT (struct bdi_writeback*,struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  domain_dirty_limits (struct dirty_throttle_control* const) ; 
 int /*<<< orphan*/  global_dirtyable_memory () ; 
 scalar_t__ global_node_page_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdtc_calc_avail (struct dirty_throttle_control* const,unsigned long,unsigned long) ; 
 scalar_t__ mdtc_valid (struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  mem_cgroup_wb_stats (struct bdi_writeback*,unsigned long*,unsigned long*,scalar_t__*,unsigned long*) ; 
 scalar_t__ wb_calc_thresh (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 

bool wb_over_bg_thresh(struct bdi_writeback *wb)
{
	struct dirty_throttle_control gdtc_stor = { GDTC_INIT(wb) };
	struct dirty_throttle_control mdtc_stor = { MDTC_INIT(wb, &gdtc_stor) };
	struct dirty_throttle_control * const gdtc = &gdtc_stor;
	struct dirty_throttle_control * const mdtc = mdtc_valid(&mdtc_stor) ?
						     &mdtc_stor : NULL;

	/*
	 * Similar to balance_dirty_pages() but ignores pages being written
	 * as we're trying to decide whether to put more under writeback.
	 */
	gdtc->avail = global_dirtyable_memory();
	gdtc->dirty = global_node_page_state(NR_FILE_DIRTY) +
		      global_node_page_state(NR_UNSTABLE_NFS);
	domain_dirty_limits(gdtc);

	if (gdtc->dirty > gdtc->bg_thresh)
		return true;

	if (wb_stat(wb, WB_RECLAIMABLE) >
	    wb_calc_thresh(gdtc->wb, gdtc->bg_thresh))
		return true;

	if (mdtc) {
		unsigned long filepages, headroom, writeback;

		mem_cgroup_wb_stats(wb, &filepages, &headroom, &mdtc->dirty,
				    &writeback);
		mdtc_calc_avail(mdtc, filepages, headroom);
		domain_dirty_limits(mdtc);	/* ditto, ignore writeback */

		if (mdtc->dirty > mdtc->bg_thresh)
			return true;

		if (wb_stat(wb, WB_RECLAIMABLE) >
		    wb_calc_thresh(mdtc->wb, mdtc->bg_thresh))
			return true;
	}

	return false;
}