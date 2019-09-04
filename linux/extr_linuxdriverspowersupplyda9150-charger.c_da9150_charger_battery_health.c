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
#define  DA9150_CHG_STAT_ACT 132 
 int DA9150_CHG_STAT_MASK ; 
#define  DA9150_CHG_STAT_PRE 131 
#define  DA9150_CHG_STAT_TIME 130 
 int DA9150_CHG_TEMP_MASK ; 
#define  DA9150_CHG_TEMP_OVER 129 
#define  DA9150_CHG_TEMP_UNDER 128 
 int /*<<< orphan*/  DA9150_STATUS_J ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_COLD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_DEAD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_health(struct da9150_charger *charger,
					 union power_supply_propval *val)
{
	u8 reg;

	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_J);

	/* Check if temperature limit reached */
	switch (reg & DA9150_CHG_TEMP_MASK) {
	case DA9150_CHG_TEMP_UNDER:
		val->intval = POWER_SUPPLY_HEALTH_COLD;
		return 0;
	case DA9150_CHG_TEMP_OVER:
		val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		return 0;
	default:
		break;
	}

	/* Check for other health states */
	switch (reg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PRE:
		val->intval = POWER_SUPPLY_HEALTH_DEAD;
		break;
	case DA9150_CHG_STAT_TIME:
		val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;
	default:
		val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	}

	return 0;
}