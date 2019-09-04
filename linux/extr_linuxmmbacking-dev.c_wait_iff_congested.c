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
typedef  int /*<<< orphan*/  wait_queue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/ * congestion_wqh ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long io_schedule_timeout (long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_usecs (unsigned long) ; 
 int /*<<< orphan*/ * nr_wb_congested ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_writeback_wait_iff_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

long wait_iff_congested(int sync, long timeout)
{
	long ret;
	unsigned long start = jiffies;
	DEFINE_WAIT(wait);
	wait_queue_head_t *wqh = &congestion_wqh[sync];

	/*
	 * If there is no congestion, yield if necessary instead
	 * of sleeping on the congestion queue
	 */
	if (atomic_read(&nr_wb_congested[sync]) == 0) {
		cond_resched();

		/* In case we scheduled, work out time remaining */
		ret = timeout - (jiffies - start);
		if (ret < 0)
			ret = 0;

		goto out;
	}

	/* Sleep until uncongested or a write happens */
	prepare_to_wait(wqh, &wait, TASK_UNINTERRUPTIBLE);
	ret = io_schedule_timeout(timeout);
	finish_wait(wqh, &wait);

out:
	trace_writeback_wait_iff_congested(jiffies_to_usecs(timeout),
					jiffies_to_usecs(jiffies - start));

	return ret;
}