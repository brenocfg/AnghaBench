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
union power_supply_propval {int intval; } ;
struct wm97xx_batt_pdata {int batt_tech; int max_voltage; int min_voltage; int /*<<< orphan*/  temp_aux; int /*<<< orphan*/  batt_aux; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_PRESENT 134 
#define  POWER_SUPPLY_PROP_STATUS 133 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 132 
#define  POWER_SUPPLY_PROP_TEMP 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int bat_status ; 
 struct wm97xx_batt_pdata* power_supply_get_drvdata (struct power_supply*) ; 
 int wm97xx_read_bat (struct power_supply*) ; 
 int wm97xx_read_temp (struct power_supply*) ; 

__attribute__((used)) static int wm97xx_bat_get_property(struct power_supply *bat_ps,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct wm97xx_batt_pdata *pdata = power_supply_get_drvdata(bat_ps);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = bat_status;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = pdata->batt_tech;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (pdata->batt_aux >= 0)
			val->intval = wm97xx_read_bat(bat_ps);
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		if (pdata->temp_aux >= 0)
			val->intval = wm97xx_read_temp(bat_ps);
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		if (pdata->max_voltage >= 0)
			val->intval = pdata->max_voltage;
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		if (pdata->min_voltage >= 0)
			val->intval = pdata->min_voltage;
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}