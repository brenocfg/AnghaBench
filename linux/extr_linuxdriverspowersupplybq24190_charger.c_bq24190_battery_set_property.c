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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct power_supply {int dummy; } ;
struct bq24190_dev_info {int /*<<< orphan*/  dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_TEMP_ALERT_MAX 128 
 int bq24190_battery_set_online (struct bq24190_dev_info*,union power_supply_propval const*) ; 
 int bq24190_battery_set_temp_alert_max (struct bq24190_dev_info*,union power_supply_propval const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct bq24190_dev_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bq24190_battery_set_property(struct power_supply *psy,
		enum power_supply_property psp,
		const union power_supply_propval *val)
{
	struct bq24190_dev_info *bdi = power_supply_get_drvdata(psy);
	int ret;

	dev_warn(bdi->dev, "warning: /sys/class/power_supply/bq24190-battery is deprecated\n");
	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runtime_get_sync(bdi->dev);
	if (ret < 0)
		return ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_battery_set_online(bdi, val);
		break;
	case POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = bq24190_battery_set_temp_alert_max(bdi, val);
		break;
	default:
		ret = -EINVAL;
	}

	pm_runtime_mark_last_busy(bdi->dev);
	pm_runtime_put_autosuspend(bdi->dev);

	return ret;
}