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
struct charger_manager {int /*<<< orphan*/  fullbatt_vchk_work; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_monitor_work ; 
 scalar_t__ cm_need_to_awake () ; 
 scalar_t__ cm_setup_timer () ; 
 int cm_suspended ; 
 scalar_t__ cm_timer_set ; 
 struct charger_manager* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  setup_polling ; 

__attribute__((used)) static int cm_suspend_prepare(struct device *dev)
{
	struct charger_manager *cm = dev_get_drvdata(dev);

	if (cm_need_to_awake())
		return -EBUSY;

	if (!cm_suspended)
		cm_suspended = true;

	cm_timer_set = cm_setup_timer();

	if (cm_timer_set) {
		cancel_work_sync(&setup_polling);
		cancel_delayed_work_sync(&cm_monitor_work);
		cancel_delayed_work(&cm->fullbatt_vchk_work);
	}

	return 0;
}