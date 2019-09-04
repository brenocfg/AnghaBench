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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct bq24190_dev_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  model_name; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_MANUFACTURER ; 
 int ENODATA ; 
#define  POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT 142 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 141 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 140 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 139 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 138 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 137 
#define  POWER_SUPPLY_PROP_HEALTH 136 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 135 
#define  POWER_SUPPLY_PROP_MANUFACTURER 134 
#define  POWER_SUPPLY_PROP_MODEL_NAME 133 
#define  POWER_SUPPLY_PROP_ONLINE 132 
#define  POWER_SUPPLY_PROP_PRECHARGE_CURRENT 131 
#define  POWER_SUPPLY_PROP_SCOPE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_TEMP_ALERT_MAX 128 
 int /*<<< orphan*/  POWER_SUPPLY_SCOPE_SYSTEM ; 
 int bq24190_charger_get_charge_term (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_charge_type (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_current (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_current_max (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_health (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_iinlimit (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_online (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_precharge (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_status (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_temp_alert_max (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_voltage (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int bq24190_charger_get_voltage_max (struct bq24190_dev_info*,union power_supply_propval*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct bq24190_dev_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bq24190_charger_get_property(struct power_supply *psy,
		enum power_supply_property psp, union power_supply_propval *val)
{
	struct bq24190_dev_info *bdi = power_supply_get_drvdata(psy);
	int ret;

	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runtime_get_sync(bdi->dev);
	if (ret < 0)
		return ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = bq24190_charger_get_charge_type(bdi, val);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = bq24190_charger_get_health(bdi, val);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_charger_get_online(bdi, val);
		break;
	case POWER_SUPPLY_PROP_STATUS:
		ret = bq24190_charger_get_status(bdi, val);
		break;
	case POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret =  bq24190_charger_get_temp_alert_max(bdi, val);
		break;
	case POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq24190_charger_get_precharge(bdi, val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = bq24190_charger_get_charge_term(bdi, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq24190_charger_get_current(bdi, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		ret = bq24190_charger_get_current_max(bdi, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq24190_charger_get_voltage(bdi, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		ret = bq24190_charger_get_voltage_max(bdi, val);
		break;
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq24190_charger_get_iinlimit(bdi, val);
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_SYSTEM;
		ret = 0;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bdi->model_name;
		ret = 0;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ24190_MANUFACTURER;
		ret = 0;
		break;
	default:
		ret = -ENODATA;
	}

	pm_runtime_mark_last_busy(bdi->dev);
	pm_runtime_put_autosuspend(bdi->dev);

	return ret;
}