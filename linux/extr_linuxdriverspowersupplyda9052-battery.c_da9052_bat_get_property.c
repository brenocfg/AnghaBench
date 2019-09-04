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
struct power_supply {int dummy; } ;
struct da9052_battery {int /*<<< orphan*/  da9052; int /*<<< orphan*/  charger_type; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int DA9052_BAT_CUTOFF_VOLT ; 
 int /*<<< orphan*/  DA9052_NOCHARGER ; 
 int EINVAL ; 
 int ENODEV ; 
#define  POWER_SUPPLY_PROP_CAPACITY 137 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 136 
#define  POWER_SUPPLY_PROP_HEALTH 135 
#define  POWER_SUPPLY_PROP_ONLINE 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int da9052_adc_read_temp (int /*<<< orphan*/ ) ; 
 int da9052_bat_check_health (struct da9052_battery*,int*) ; 
 int da9052_bat_check_presence (struct da9052_battery*,int*) ; 
 int da9052_bat_check_status (struct da9052_battery*,int*) ; 
 int da9052_bat_read_capacity (struct da9052_battery*,int*) ; 
 int da9052_bat_read_volt (struct da9052_battery*,int*) ; 
 int da9052_read_chg_current (struct da9052_battery*,int*) ; 
 struct da9052_battery* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int da9052_bat_get_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    union power_supply_propval *val)
{
	int ret;
	int illegal;
	struct da9052_battery *bat = power_supply_get_drvdata(psy);

	ret = da9052_bat_check_presence(bat, &illegal);
	if (ret < 0)
		return ret;

	if (illegal && psp != POWER_SUPPLY_PROP_PRESENT)
		return -ENODEV;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = da9052_bat_check_status(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval =
			(bat->charger_type == DA9052_NOCHARGER) ? 0 : 1;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		ret = da9052_bat_check_presence(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = da9052_bat_check_health(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = DA9052_BAT_CUTOFF_VOLT * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = da9052_bat_read_volt(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9052_read_chg_current(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = da9052_bat_read_capacity(bat, &val->intval);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = da9052_adc_read_temp(bat->da9052);
		ret = val->intval;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	default:
		return -EINVAL;
	}
	return ret;
}