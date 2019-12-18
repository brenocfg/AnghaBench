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
typedef  unsigned long u64 ;
struct dirty_throttle_control {unsigned long dirty; unsigned long wb_dirty; unsigned long wb_thresh; unsigned long wb_bg_thresh; unsigned long thresh; unsigned long bg_thresh; scalar_t__ pos_ratio; int /*<<< orphan*/  avail; int /*<<< orphan*/  member_0; } ;
struct bdi_writeback {int dirty_exceeded; unsigned long dirty_ratelimit; unsigned long dirty_sleep; int /*<<< orphan*/  list_lock; scalar_t__ bw_time_stamp; struct backing_dev_info* bdi; } ;
struct backing_dev_info {int capabilities; } ;
struct TYPE_3__ {unsigned long dirty_paused_when; long nr_dirtied_pause; scalar_t__ nr_dirtied; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_INTERVAL ; 
 int BDI_CAP_STRICTLIMIT ; 
 int /*<<< orphan*/  GDTC_INIT (struct bdi_writeback*) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  MDTC_INIT (struct bdi_writeback*,struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 unsigned long RATELIMIT_CALC_SHIFT ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wb_update_bandwidth (struct dirty_throttle_control* const,struct dirty_throttle_control* const,unsigned long,int) ; 
 TYPE_1__* current ; 
 unsigned long dirty_freerun_ceiling (unsigned long,unsigned long) ; 
 unsigned long dirty_poll_interval (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  domain_dirty_limits (struct dirty_throttle_control* const) ; 
 scalar_t__ fatal_signal_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  global_dirtyable_memory () ; 
 unsigned long global_node_page_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule_timeout (long) ; 
 unsigned long jiffies ; 
 scalar_t__ laptop_mode ; 
 int /*<<< orphan*/  mdtc_calc_avail (struct dirty_throttle_control* const,unsigned long,unsigned long) ; 
 scalar_t__ mdtc_valid (struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  mem_cgroup_flush_foreign (struct bdi_writeback*) ; 
 int /*<<< orphan*/  mem_cgroup_wb_stats (struct bdi_writeback*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 long min (long,long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  trace_balance_dirty_pages (struct bdi_writeback*,scalar_t__,unsigned long,scalar_t__,scalar_t__,scalar_t__,unsigned long,unsigned long,unsigned long,long,long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wb_dirty_limits (struct dirty_throttle_control* const) ; 
 long wb_max_pause (struct bdi_writeback*,scalar_t__) ; 
 long wb_min_pause (struct bdi_writeback*,long,unsigned long,unsigned long,int*) ; 
 int /*<<< orphan*/  wb_position_ratio (struct dirty_throttle_control* const) ; 
 int /*<<< orphan*/  wb_start_background_writeback (struct bdi_writeback*) ; 
 scalar_t__ wb_stat_error () ; 
 scalar_t__ writeback_in_progress (struct bdi_writeback*) ; 

__attribute__((used)) static void balance_dirty_pages(struct bdi_writeback *wb,
				unsigned long pages_dirtied)
{
	struct dirty_throttle_control gdtc_stor = { GDTC_INIT(wb) };
	struct dirty_throttle_control mdtc_stor = { MDTC_INIT(wb, &gdtc_stor) };
	struct dirty_throttle_control * const gdtc = &gdtc_stor;
	struct dirty_throttle_control * const mdtc = mdtc_valid(&mdtc_stor) ?
						     &mdtc_stor : NULL;
	struct dirty_throttle_control *sdtc;
	unsigned long nr_reclaimable;	/* = file_dirty + unstable_nfs */
	long period;
	long pause;
	long max_pause;
	long min_pause;
	int nr_dirtied_pause;
	bool dirty_exceeded = false;
	unsigned long task_ratelimit;
	unsigned long dirty_ratelimit;
	struct backing_dev_info *bdi = wb->bdi;
	bool strictlimit = bdi->capabilities & BDI_CAP_STRICTLIMIT;
	unsigned long start_time = jiffies;

	for (;;) {
		unsigned long now = jiffies;
		unsigned long dirty, thresh, bg_thresh;
		unsigned long m_dirty = 0;	/* stop bogus uninit warnings */
		unsigned long m_thresh = 0;
		unsigned long m_bg_thresh = 0;

		/*
		 * Unstable writes are a feature of certain networked
		 * filesystems (i.e. NFS) in which data may have been
		 * written to the server's write cache, but has not yet
		 * been flushed to permanent storage.
		 */
		nr_reclaimable = global_node_page_state(NR_FILE_DIRTY) +
					global_node_page_state(NR_UNSTABLE_NFS);
		gdtc->avail = global_dirtyable_memory();
		gdtc->dirty = nr_reclaimable + global_node_page_state(NR_WRITEBACK);

		domain_dirty_limits(gdtc);

		if (unlikely(strictlimit)) {
			wb_dirty_limits(gdtc);

			dirty = gdtc->wb_dirty;
			thresh = gdtc->wb_thresh;
			bg_thresh = gdtc->wb_bg_thresh;
		} else {
			dirty = gdtc->dirty;
			thresh = gdtc->thresh;
			bg_thresh = gdtc->bg_thresh;
		}

		if (mdtc) {
			unsigned long filepages, headroom, writeback;

			/*
			 * If @wb belongs to !root memcg, repeat the same
			 * basic calculations for the memcg domain.
			 */
			mem_cgroup_wb_stats(wb, &filepages, &headroom,
					    &mdtc->dirty, &writeback);
			mdtc->dirty += writeback;
			mdtc_calc_avail(mdtc, filepages, headroom);

			domain_dirty_limits(mdtc);

			if (unlikely(strictlimit)) {
				wb_dirty_limits(mdtc);
				m_dirty = mdtc->wb_dirty;
				m_thresh = mdtc->wb_thresh;
				m_bg_thresh = mdtc->wb_bg_thresh;
			} else {
				m_dirty = mdtc->dirty;
				m_thresh = mdtc->thresh;
				m_bg_thresh = mdtc->bg_thresh;
			}
		}

		/*
		 * Throttle it only when the background writeback cannot
		 * catch-up. This avoids (excessively) small writeouts
		 * when the wb limits are ramping up in case of !strictlimit.
		 *
		 * In strictlimit case make decision based on the wb counters
		 * and limits. Small writeouts when the wb limits are ramping
		 * up are the price we consciously pay for strictlimit-ing.
		 *
		 * If memcg domain is in effect, @dirty should be under
		 * both global and memcg freerun ceilings.
		 */
		if (dirty <= dirty_freerun_ceiling(thresh, bg_thresh) &&
		    (!mdtc ||
		     m_dirty <= dirty_freerun_ceiling(m_thresh, m_bg_thresh))) {
			unsigned long intv = dirty_poll_interval(dirty, thresh);
			unsigned long m_intv = ULONG_MAX;

			current->dirty_paused_when = now;
			current->nr_dirtied = 0;
			if (mdtc)
				m_intv = dirty_poll_interval(m_dirty, m_thresh);
			current->nr_dirtied_pause = min(intv, m_intv);
			break;
		}

		if (unlikely(!writeback_in_progress(wb)))
			wb_start_background_writeback(wb);

		mem_cgroup_flush_foreign(wb);

		/*
		 * Calculate global domain's pos_ratio and select the
		 * global dtc by default.
		 */
		if (!strictlimit)
			wb_dirty_limits(gdtc);

		dirty_exceeded = (gdtc->wb_dirty > gdtc->wb_thresh) &&
			((gdtc->dirty > gdtc->thresh) || strictlimit);

		wb_position_ratio(gdtc);
		sdtc = gdtc;

		if (mdtc) {
			/*
			 * If memcg domain is in effect, calculate its
			 * pos_ratio.  @wb should satisfy constraints from
			 * both global and memcg domains.  Choose the one
			 * w/ lower pos_ratio.
			 */
			if (!strictlimit)
				wb_dirty_limits(mdtc);

			dirty_exceeded |= (mdtc->wb_dirty > mdtc->wb_thresh) &&
				((mdtc->dirty > mdtc->thresh) || strictlimit);

			wb_position_ratio(mdtc);
			if (mdtc->pos_ratio < gdtc->pos_ratio)
				sdtc = mdtc;
		}

		if (dirty_exceeded && !wb->dirty_exceeded)
			wb->dirty_exceeded = 1;

		if (time_is_before_jiffies(wb->bw_time_stamp +
					   BANDWIDTH_INTERVAL)) {
			spin_lock(&wb->list_lock);
			__wb_update_bandwidth(gdtc, mdtc, start_time, true);
			spin_unlock(&wb->list_lock);
		}

		/* throttle according to the chosen dtc */
		dirty_ratelimit = wb->dirty_ratelimit;
		task_ratelimit = ((u64)dirty_ratelimit * sdtc->pos_ratio) >>
							RATELIMIT_CALC_SHIFT;
		max_pause = wb_max_pause(wb, sdtc->wb_dirty);
		min_pause = wb_min_pause(wb, max_pause,
					 task_ratelimit, dirty_ratelimit,
					 &nr_dirtied_pause);

		if (unlikely(task_ratelimit == 0)) {
			period = max_pause;
			pause = max_pause;
			goto pause;
		}
		period = HZ * pages_dirtied / task_ratelimit;
		pause = period;
		if (current->dirty_paused_when)
			pause -= now - current->dirty_paused_when;
		/*
		 * For less than 1s think time (ext3/4 may block the dirtier
		 * for up to 800ms from time to time on 1-HDD; so does xfs,
		 * however at much less frequency), try to compensate it in
		 * future periods by updating the virtual time; otherwise just
		 * do a reset, as it may be a light dirtier.
		 */
		if (pause < min_pause) {
			trace_balance_dirty_pages(wb,
						  sdtc->thresh,
						  sdtc->bg_thresh,
						  sdtc->dirty,
						  sdtc->wb_thresh,
						  sdtc->wb_dirty,
						  dirty_ratelimit,
						  task_ratelimit,
						  pages_dirtied,
						  period,
						  min(pause, 0L),
						  start_time);
			if (pause < -HZ) {
				current->dirty_paused_when = now;
				current->nr_dirtied = 0;
			} else if (period) {
				current->dirty_paused_when += period;
				current->nr_dirtied = 0;
			} else if (current->nr_dirtied_pause <= pages_dirtied)
				current->nr_dirtied_pause += pages_dirtied;
			break;
		}
		if (unlikely(pause > max_pause)) {
			/* for occasional dropped task_ratelimit */
			now += min(pause - max_pause, max_pause);
			pause = max_pause;
		}

pause:
		trace_balance_dirty_pages(wb,
					  sdtc->thresh,
					  sdtc->bg_thresh,
					  sdtc->dirty,
					  sdtc->wb_thresh,
					  sdtc->wb_dirty,
					  dirty_ratelimit,
					  task_ratelimit,
					  pages_dirtied,
					  period,
					  pause,
					  start_time);
		__set_current_state(TASK_KILLABLE);
		wb->dirty_sleep = now;
		io_schedule_timeout(pause);

		current->dirty_paused_when = now + pause;
		current->nr_dirtied = 0;
		current->nr_dirtied_pause = nr_dirtied_pause;

		/*
		 * This is typically equal to (dirty < thresh) and can also
		 * keep "1000+ dd on a slow USB stick" under control.
		 */
		if (task_ratelimit)
			break;

		/*
		 * In the case of an unresponding NFS server and the NFS dirty
		 * pages exceeds dirty_thresh, give the other good wb's a pipe
		 * to go through, so that tasks on them still remain responsive.
		 *
		 * In theory 1 page is enough to keep the consumer-producer
		 * pipe going: the flusher cleans 1 page => the task dirties 1
		 * more page. However wb_dirty has accounting errors.  So use
		 * the larger and more IO friendly wb_stat_error.
		 */
		if (sdtc->wb_dirty <= wb_stat_error())
			break;

		if (fatal_signal_pending(current))
			break;
	}

	if (!dirty_exceeded && wb->dirty_exceeded)
		wb->dirty_exceeded = 0;

	if (writeback_in_progress(wb))
		return;

	/*
	 * In laptop mode, we wait until hitting the higher threshold before
	 * starting background writeout, and then write out all the way down
	 * to the lower threshold.  So slow writers cause minimal disk activity.
	 *
	 * In normal mode, we start background writeout at the lower
	 * background_thresh, to keep the amount of dirty memory low.
	 */
	if (laptop_mode)
		return;

	if (nr_reclaimable > gdtc->bg_thresh)
		wb_start_background_writeback(wb);
}