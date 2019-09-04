#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct TYPE_2__ {int technology; int voltage_min_design; int voltage_max_design; int charge_full_design; int /*<<< orphan*/  name; } ;
struct smb347_charger_platform_data {TYPE_1__ battery_info; } ;
struct smb347_charger {struct smb347_charger_platform_data* pdata; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 134 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 133 
#define  POWER_SUPPLY_PROP_MODEL_NAME 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 128 
 struct smb347_charger* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  smb347_charging_status (struct smb347_charger*) ; 
 int smb347_get_charging_status (struct smb347_charger*) ; 
 int /*<<< orphan*/  smb347_is_ps_online (struct smb347_charger*) ; 
 int smb347_update_ps_status (struct smb347_charger*) ; 

__attribute__((used)) static int smb347_battery_get_property(struct power_supply *psy,
				       enum power_supply_property prop,
				       union power_supply_propval *val)
{
	struct smb347_charger *smb = power_supply_get_drvdata(psy);
	const struct smb347_charger_platform_data *pdata = smb->pdata;
	int ret;

	ret = smb347_update_ps_status(smb);
	if (ret < 0)
		return ret;

	switch (prop) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = smb347_get_charging_status(smb);
		if (ret < 0)
			return ret;
		val->intval = ret;
		break;

	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		if (!smb347_is_ps_online(smb))
			return -ENODATA;

		/*
		 * We handle trickle and pre-charging the same, and taper
		 * and none the same.
		 */
		switch (smb347_charging_status(smb)) {
		case 1:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			break;
		case 2:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			break;
		default:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			break;
		}
		break;

	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = pdata->battery_info.technology;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = pdata->battery_info.voltage_min_design;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = pdata->battery_info.voltage_max_design;
		break;

	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = pdata->battery_info.charge_full_design;
		break;

	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = pdata->battery_info.name;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}