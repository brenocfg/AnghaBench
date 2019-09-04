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
struct rtc_device {int irq_freq; int /*<<< orphan*/  pie_timer; } ;
typedef  int ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtc_update_hrtimer(struct rtc_device *rtc, int enabled)
{
	/*
	 * We always cancel the timer here first, because otherwise
	 * we could run into BUG_ON(timer->state != HRTIMER_STATE_CALLBACK);
	 * when we manage to start the timer before the callback
	 * returns HRTIMER_RESTART.
	 *
	 * We cannot use hrtimer_cancel() here as a running callback
	 * could be blocked on rtc->irq_task_lock and hrtimer_cancel()
	 * would spin forever.
	 */
	if (hrtimer_try_to_cancel(&rtc->pie_timer) < 0)
		return -1;

	if (enabled) {
		ktime_t period = NSEC_PER_SEC / rtc->irq_freq;

		hrtimer_start(&rtc->pie_timer, period, HRTIMER_MODE_REL);
	}
	return 0;
}