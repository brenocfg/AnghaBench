#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_2__* desc; TYPE_1__ dev; } ;
struct lp8727_platform_data {int /*<<< orphan*/  (* get_batt_temp ) () ;int /*<<< orphan*/  (* get_batt_capacity ) () ;int /*<<< orphan*/  (* get_batt_level ) () ;int /*<<< orphan*/  (* get_batt_present ) () ;} ;
struct lp8727_chg {int /*<<< orphan*/  devid; struct lp8727_platform_data* pdata; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
typedef  enum lp8727_die_temp { ____Placeholder_lp8727_die_temp } lp8727_die_temp ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int LP8727_CHGSTAT ; 
 int /*<<< orphan*/  LP8727_STATUS1 ; 
 int /*<<< orphan*/  LP8727_STATUS2 ; 
 int LP8727_STAT_EOC ; 
 int LP8727_TEMP_SHIFT ; 
 int LP8727_TEMP_STAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
#define  POWER_SUPPLY_PROP_CAPACITY 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_PRESENT 131 
#define  POWER_SUPPLY_PROP_STATUS 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 struct lp8727_chg* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8727_is_charger_attached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8727_is_high_temperature (int) ; 
 int /*<<< orphan*/  lp8727_read_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 

__attribute__((used)) static int lp8727_battery_get_property(struct power_supply *psy,
				       enum power_supply_property psp,
				       union power_supply_propval *val)
{
	struct lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);
	struct lp8727_platform_data *pdata = pchg->pdata;
	enum lp8727_die_temp temp;
	u8 read;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (!lp8727_is_charger_attached(psy->desc->name, pchg->devid)) {
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
			return 0;
		}

		lp8727_read_byte(pchg, LP8727_STATUS1, &read);

		val->intval = (read & LP8727_CHGSTAT) == LP8727_STAT_EOC ?
				POWER_SUPPLY_STATUS_FULL :
				POWER_SUPPLY_STATUS_CHARGING;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		lp8727_read_byte(pchg, LP8727_STATUS2, &read);
		temp = (read & LP8727_TEMP_STAT) >> LP8727_TEMP_SHIFT;

		val->intval = lp8727_is_high_temperature(temp) ?
			POWER_SUPPLY_HEALTH_OVERHEAT :
			POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		if (!pdata)
			return -EINVAL;

		if (pdata->get_batt_present)
			val->intval = pdata->get_batt_present();
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (!pdata)
			return -EINVAL;

		if (pdata->get_batt_level)
			val->intval = pdata->get_batt_level();
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		if (!pdata)
			return -EINVAL;

		if (pdata->get_batt_capacity)
			val->intval = pdata->get_batt_capacity();
		break;
	case POWER_SUPPLY_PROP_TEMP:
		if (!pdata)
			return -EINVAL;

		if (pdata->get_batt_temp)
			val->intval = pdata->get_batt_temp();
		break;
	default:
		break;
	}

	return 0;
}