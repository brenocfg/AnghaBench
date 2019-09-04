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
#define  DA9150_CHG_STAT_ACT 131 
#define  DA9150_CHG_STAT_CC 130 
#define  DA9150_CHG_STAT_CV 129 
 int DA9150_CHG_STAT_MASK ; 
#define  DA9150_CHG_STAT_PRE 128 
 int /*<<< orphan*/  DA9150_STATUS_J ; 
 int /*<<< orphan*/  POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int /*<<< orphan*/  POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int /*<<< orphan*/  POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_charge_type(struct da9150_charger *charger,
					      union power_supply_propval *val)
{
	u8 reg;

	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_J);

	switch (reg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_CC:
		val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		break;
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PRE:
	case DA9150_CHG_STAT_CV:
		val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		break;
	default:
		val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		break;
	}

	return 0;
}