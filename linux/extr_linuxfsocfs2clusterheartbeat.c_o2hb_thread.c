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
struct o2hb_region {int hr_node_deleted; int hr_last_hb_status; unsigned int hr_timeout_ms; int hr_blocks; int /*<<< orphan*/  hr_aborted_start; int /*<<< orphan*/  hr_unclean_stop; int /*<<< orphan*/ * hr_slots; } ;
struct o2hb_bio_wait_ctxt {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_NICE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int ML_HEARTBEAT ; 
 int ML_KTHREAD ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned int) ; 
 int /*<<< orphan*/  o2hb_disarm_timeout (struct o2hb_region*) ; 
 int o2hb_do_disk_heartbeat (struct o2hb_region*) ; 
 int o2hb_issue_node_write (struct o2hb_region*,struct o2hb_bio_wait_ctxt*) ; 
 int /*<<< orphan*/  o2hb_prepare_block (struct o2hb_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_shutdown_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_steady_queue ; 
 int /*<<< orphan*/  o2hb_wait_on_io (struct o2hb_bio_wait_ctxt*) ; 
 int o2nm_depend_this_node () ; 
 int /*<<< orphan*/  o2nm_undepend_this_node () ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2hb_thread(void *data)
{
	int i, ret;
	struct o2hb_region *reg = data;
	struct o2hb_bio_wait_ctxt write_wc;
	ktime_t before_hb, after_hb;
	unsigned int elapsed_msec;

	mlog(ML_HEARTBEAT|ML_KTHREAD, "hb thread running\n");

	set_user_nice(current, MIN_NICE);

	/* Pin node */
	ret = o2nm_depend_this_node();
	if (ret) {
		mlog(ML_ERROR, "Node has been deleted, ret = %d\n", ret);
		reg->hr_node_deleted = 1;
		wake_up(&o2hb_steady_queue);
		return 0;
	}

	while (!kthread_should_stop() &&
	       !reg->hr_unclean_stop && !reg->hr_aborted_start) {
		/* We track the time spent inside
		 * o2hb_do_disk_heartbeat so that we avoid more than
		 * hr_timeout_ms between disk writes. On busy systems
		 * this should result in a heartbeat which is less
		 * likely to time itself out. */
		before_hb = ktime_get_real();

		ret = o2hb_do_disk_heartbeat(reg);
		reg->hr_last_hb_status = ret;

		after_hb = ktime_get_real();

		elapsed_msec = (unsigned int)
				ktime_ms_delta(after_hb, before_hb);

		mlog(ML_HEARTBEAT,
		     "start = %lld, end = %lld, msec = %u, ret = %d\n",
		     before_hb, after_hb, elapsed_msec, ret);

		if (!kthread_should_stop() &&
		    elapsed_msec < reg->hr_timeout_ms) {
			/* the kthread api has blocked signals for us so no
			 * need to record the return value. */
			msleep_interruptible(reg->hr_timeout_ms - elapsed_msec);
		}
	}

	o2hb_disarm_timeout(reg);

	/* unclean stop is only used in very bad situation */
	for(i = 0; !reg->hr_unclean_stop && i < reg->hr_blocks; i++)
		o2hb_shutdown_slot(&reg->hr_slots[i]);

	/* Explicit down notification - avoid forcing the other nodes
	 * to timeout on this region when we could just as easily
	 * write a clear generation - thus indicating to them that
	 * this node has left this region.
	 */
	if (!reg->hr_unclean_stop && !reg->hr_aborted_start) {
		o2hb_prepare_block(reg, 0);
		ret = o2hb_issue_node_write(reg, &write_wc);
		if (ret == 0)
			o2hb_wait_on_io(&write_wc);
		else
			mlog_errno(ret);
	}

	/* Unpin node */
	o2nm_undepend_this_node();

	mlog(ML_HEARTBEAT|ML_KTHREAD, "o2hb thread exiting\n");

	return 0;
}