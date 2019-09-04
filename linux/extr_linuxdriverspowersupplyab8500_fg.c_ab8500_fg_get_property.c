#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_6__ {int max_mah_design; int max_mah; int prev_mah; int prev_percent; int prev_level; } ;
struct TYPE_5__ {int /*<<< orphan*/  batt_id_received; int /*<<< orphan*/  batt_unknown; int /*<<< orphan*/  bat_ovv; } ;
struct ab8500_fg {int vbat; int inst_curr; int avg_curr; TYPE_3__ bat_cap; TYPE_2__ flags; TYPE_1__* bm; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {int /*<<< orphan*/  chg_unknown_bat; } ;

/* Variables and functions */
 int BATT_OVV_VALUE ; 
 int EINVAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN ; 
#define  POWER_SUPPLY_PROP_CAPACITY 138 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 137 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 136 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 135 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 134 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 133 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 132 
#define  POWER_SUPPLY_PROP_ENERGY_FULL 131 
#define  POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN 130 
#define  POWER_SUPPLY_PROP_ENERGY_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 void* ab8500_fg_convert_mah_to_uwh (struct ab8500_fg*,int) ; 
 struct ab8500_fg* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int ab8500_fg_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct ab8500_fg *di = power_supply_get_drvdata(psy);

	/*
	 * If battery is identified as unknown and charging of unknown
	 * batteries is disabled, we always report 100% capacity and
	 * capacity level UNKNOWN, since we can't calculate
	 * remaining capacity
	 */

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (di->flags.bat_ovv)
			val->intval = BATT_OVV_VALUE * 1000;
		else
			val->intval = di->vbat * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = di->inst_curr * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		val->intval = di->avg_curr * 1000;
		break;
	case POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		val->intval = ab8500_fg_convert_mah_to_uwh(di,
				di->bat_cap.max_mah_design);
		break;
	case POWER_SUPPLY_PROP_ENERGY_FULL:
		val->intval = ab8500_fg_convert_mah_to_uwh(di,
				di->bat_cap.max_mah);
		break;
	case POWER_SUPPLY_PROP_ENERGY_NOW:
		if (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->intval = ab8500_fg_convert_mah_to_uwh(di,
					di->bat_cap.max_mah);
		else
			val->intval = ab8500_fg_convert_mah_to_uwh(di,
					di->bat_cap.prev_mah);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = di->bat_cap.max_mah_design;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = di->bat_cap.max_mah;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		if (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->intval = di->bat_cap.max_mah;
		else
			val->intval = di->bat_cap.prev_mah;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		if (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->intval = 100;
		else
			val->intval = di->bat_cap.prev_percent;
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		if (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		else
			val->intval = di->bat_cap.prev_level;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}