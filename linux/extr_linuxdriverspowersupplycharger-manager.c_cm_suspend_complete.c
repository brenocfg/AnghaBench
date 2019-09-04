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
struct device {int dummy; } ;
struct charger_manager {int /*<<< orphan*/  dev; int /*<<< orphan*/  fullbatt_vchk_work; scalar_t__ fullbatt_vchk_jiffies_at; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned long CM_JIFFIES_SMALL ; 
 int /*<<< orphan*/  _cm_monitor (struct charger_manager*) ; 
 int /*<<< orphan*/  alarm_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm_expires_remaining (int /*<<< orphan*/ ) ; 
 unsigned long cm_suspend_duration_ms ; 
 int cm_suspended ; 
 int /*<<< orphan*/  cm_timer ; 
 int cm_timer_set ; 
 int /*<<< orphan*/  cm_wq ; 
 struct charger_manager* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long jiffies_to_msecs (unsigned long) ; 
 scalar_t__ ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_polling ; 
 scalar_t__ time_after_eq (unsigned long,scalar_t__) ; 

__attribute__((used)) static void cm_suspend_complete(struct device *dev)
{
	struct charger_manager *cm = dev_get_drvdata(dev);

	if (cm_suspended)
		cm_suspended = false;

	if (cm_timer_set) {
		ktime_t remain;

		alarm_cancel(cm_timer);
		cm_timer_set = false;
		remain = alarm_expires_remaining(cm_timer);
		cm_suspend_duration_ms -= ktime_to_ms(remain);
		schedule_work(&setup_polling);
	}

	_cm_monitor(cm);

	/* Re-enqueue delayed work (fullbatt_vchk_work) */
	if (cm->fullbatt_vchk_jiffies_at) {
		unsigned long delay = 0;
		unsigned long now = jiffies + CM_JIFFIES_SMALL;

		if (time_after_eq(now, cm->fullbatt_vchk_jiffies_at)) {
			delay = (unsigned long)((long)now
				- (long)(cm->fullbatt_vchk_jiffies_at));
			delay = jiffies_to_msecs(delay);
		} else {
			delay = 0;
		}

		/*
		 * Account for cm_suspend_duration_ms with assuming that
		 * timer stops in suspend.
		 */
		if (delay > cm_suspend_duration_ms)
			delay -= cm_suspend_duration_ms;
		else
			delay = 0;

		queue_delayed_work(cm_wq, &cm->fullbatt_vchk_work,
				   msecs_to_jiffies(delay));
	}
	device_set_wakeup_capable(cm->dev, false);
}