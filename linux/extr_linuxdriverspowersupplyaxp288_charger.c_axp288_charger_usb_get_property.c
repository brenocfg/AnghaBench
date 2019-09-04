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
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id_short; } ;
struct axp288_chrg_info {int cc; int max_cc; int cv; int max_cv; TYPE_1__ otg; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 134 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 133 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 132 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_PRESENT 128 
 int axp288_charger_get_vbus_inlmt (struct axp288_chrg_info*) ; 
 int axp288_charger_is_online (struct axp288_chrg_info*) ; 
 int axp288_charger_is_present (struct axp288_chrg_info*) ; 
 int axp288_get_charger_health (struct axp288_chrg_info*) ; 
 struct axp288_chrg_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int axp288_charger_usb_get_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    union power_supply_propval *val)
{
	struct axp288_chrg_info *info = power_supply_get_drvdata(psy);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		/* Check for OTG case first */
		if (info->otg.id_short) {
			val->intval = 0;
			break;
		}
		ret = axp288_charger_is_present(info);
		if (ret < 0)
			return ret;
		val->intval = ret;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		/* Check for OTG case first */
		if (info->otg.id_short) {
			val->intval = 0;
			break;
		}
		ret = axp288_charger_is_online(info);
		if (ret < 0)
			return ret;
		val->intval = ret;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = axp288_get_charger_health(info);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		val->intval = info->cc * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->intval = info->max_cc * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->intval = info->cv * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->intval = info->max_cv * 1000;
		break;
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = axp288_charger_get_vbus_inlmt(info);
		if (ret < 0)
			return ret;
		val->intval = ret;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}