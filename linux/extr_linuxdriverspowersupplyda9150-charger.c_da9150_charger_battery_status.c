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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
typedef  int u8 ;
struct da9150_charger {int /*<<< orphan*/  da9150; } ;

/* Variables and functions */
#define  DA9150_CHG_STAT_ACT 137 
#define  DA9150_CHG_STAT_BAT 136 
#define  DA9150_CHG_STAT_CC 135 
#define  DA9150_CHG_STAT_CV 134 
#define  DA9150_CHG_STAT_FULL 133 
 int DA9150_CHG_STAT_MASK ; 
#define  DA9150_CHG_STAT_OFF 132 
#define  DA9150_CHG_STAT_PRE 131 
#define  DA9150_CHG_STAT_SUSP 130 
#define  DA9150_CHG_STAT_TEMP 129 
#define  DA9150_CHG_STAT_TIME 128 
 int /*<<< orphan*/  DA9150_STATUS_H ; 
 int /*<<< orphan*/  DA9150_STATUS_J ; 
 int DA9150_VBUS_STAT_MASK ; 
 int DA9150_VBUS_STAT_OFF ; 
 int DA9150_VBUS_STAT_WAIT ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_status(struct da9150_charger *charger,
					 union power_supply_propval *val)
{
	u8 reg;

	/* Check to see if battery is discharging */
	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_H);

	if (((reg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_OFF) ||
	    ((reg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_WAIT)) {
		val->intval = POWER_SUPPLY_STATUS_DISCHARGING;

		return 0;
	}

	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_J);

	/* Now check for other states */
	switch (reg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PRE:
	case DA9150_CHG_STAT_CC:
	case DA9150_CHG_STAT_CV:
		val->intval = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case DA9150_CHG_STAT_OFF:
	case DA9150_CHG_STAT_SUSP:
	case DA9150_CHG_STAT_TEMP:
	case DA9150_CHG_STAT_TIME:
	case DA9150_CHG_STAT_BAT:
		val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	case DA9150_CHG_STAT_FULL:
		val->intval = POWER_SUPPLY_STATUS_FULL;
		break;
	default:
		val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		break;
	}

	return 0;
}