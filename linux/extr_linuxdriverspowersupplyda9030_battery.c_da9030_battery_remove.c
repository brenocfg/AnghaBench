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
struct da9030_charger {int /*<<< orphan*/  psy; int /*<<< orphan*/  work; int /*<<< orphan*/  nb; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int DA9030_EVENT_CHDET ; 
 int DA9030_EVENT_CHIOVER ; 
 int DA9030_EVENT_TBAT ; 
 int DA9030_EVENT_VBATMON ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da9030_bat_remove_debugfs (struct da9030_charger*) ; 
 int /*<<< orphan*/  da9030_set_charge (struct da9030_charger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da903x_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct da9030_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9030_battery_remove(struct platform_device *dev)
{
	struct da9030_charger *charger = platform_get_drvdata(dev);

	da9030_bat_remove_debugfs(charger);

	da903x_unregister_notifier(charger->master, &charger->nb,
				   DA9030_EVENT_CHDET | DA9030_EVENT_VBATMON |
				   DA9030_EVENT_CHIOVER | DA9030_EVENT_TBAT);
	cancel_delayed_work_sync(&charger->work);
	da9030_set_charge(charger, 0);
	power_supply_unregister(charger->psy);

	return 0;
}