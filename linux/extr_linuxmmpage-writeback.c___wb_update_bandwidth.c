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
struct dirty_throttle_control {struct bdi_writeback* wb; } ;
struct bdi_writeback {unsigned long bw_time_stamp; unsigned long dirtied_stamp; unsigned long written_stamp; int /*<<< orphan*/ * stat; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 unsigned long BANDWIDTH_INTERVAL ; 
 int /*<<< orphan*/  CONFIG_CGROUP_WRITEBACK ; 
 unsigned long HZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t WB_DIRTIED ; 
 size_t WB_WRITTEN ; 
 int /*<<< orphan*/  domain_update_bandwidth (struct dirty_throttle_control*,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long percpu_counter_read (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wb_update_dirty_ratelimit (struct dirty_throttle_control*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wb_update_write_bandwidth (struct bdi_writeback*,unsigned long,unsigned long) ; 

__attribute__((used)) static void __wb_update_bandwidth(struct dirty_throttle_control *gdtc,
				  struct dirty_throttle_control *mdtc,
				  unsigned long start_time,
				  bool update_ratelimit)
{
	struct bdi_writeback *wb = gdtc->wb;
	unsigned long now = jiffies;
	unsigned long elapsed = now - wb->bw_time_stamp;
	unsigned long dirtied;
	unsigned long written;

	lockdep_assert_held(&wb->list_lock);

	/*
	 * rate-limit, only update once every 200ms.
	 */
	if (elapsed < BANDWIDTH_INTERVAL)
		return;

	dirtied = percpu_counter_read(&wb->stat[WB_DIRTIED]);
	written = percpu_counter_read(&wb->stat[WB_WRITTEN]);

	/*
	 * Skip quiet periods when disk bandwidth is under-utilized.
	 * (at least 1s idle time between two flusher runs)
	 */
	if (elapsed > HZ && time_before(wb->bw_time_stamp, start_time))
		goto snapshot;

	if (update_ratelimit) {
		domain_update_bandwidth(gdtc, now);
		wb_update_dirty_ratelimit(gdtc, dirtied, elapsed);

		/*
		 * @mdtc is always NULL if !CGROUP_WRITEBACK but the
		 * compiler has no way to figure that out.  Help it.
		 */
		if (IS_ENABLED(CONFIG_CGROUP_WRITEBACK) && mdtc) {
			domain_update_bandwidth(mdtc, now);
			wb_update_dirty_ratelimit(mdtc, dirtied, elapsed);
		}
	}
	wb_update_write_bandwidth(wb, elapsed, written);

snapshot:
	wb->dirtied_stamp = dirtied;
	wb->written_stamp = written;
	wb->bw_time_stamp = now;
}