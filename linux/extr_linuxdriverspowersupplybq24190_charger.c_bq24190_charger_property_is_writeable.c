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
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 133 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 132 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 131 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_TEMP_ALERT_MAX 128 

__attribute__((used)) static int bq24190_charger_property_is_writeable(struct power_supply *psy,
		enum power_supply_property psp)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
	case POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		return 1;
	default:
		return 0;
	}
}