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
struct platform_device {int dummy; } ;
struct abx500_chargalg {int /*<<< orphan*/  chargalg_psy; int /*<<< orphan*/  chargalg_wq; int /*<<< orphan*/  chargalg_work; int /*<<< orphan*/  chargalg_wd_work; int /*<<< orphan*/  chargalg_periodic_work; int /*<<< orphan*/  maintenance_timer; int /*<<< orphan*/  safety_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  abx500_chargalg_sysfs_exit (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 struct abx500_chargalg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abx500_chargalg_remove(struct platform_device *pdev)
{
	struct abx500_chargalg *di = platform_get_drvdata(pdev);

	/* sysfs interface to enable/disbale charging from user space */
	abx500_chargalg_sysfs_exit(di);

	hrtimer_cancel(&di->safety_timer);
	hrtimer_cancel(&di->maintenance_timer);

	cancel_delayed_work_sync(&di->chargalg_periodic_work);
	cancel_delayed_work_sync(&di->chargalg_wd_work);
	cancel_work_sync(&di->chargalg_work);

	/* Delete the work queue */
	destroy_workqueue(di->chargalg_wq);

	power_supply_unregister(di->chargalg_psy);

	return 0;
}