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
union power_supply_propval {void* intval; } ;
struct power_supply {int dummy; } ;
struct goldfish_battery_data {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BATTERY_CAPACITY ; 
 int /*<<< orphan*/  BATTERY_HEALTH ; 
 int /*<<< orphan*/  BATTERY_PRESENT ; 
 int /*<<< orphan*/  BATTERY_STATUS ; 
 int EINVAL ; 
 void* GOLDFISH_BATTERY_READ (struct goldfish_battery_data*,int /*<<< orphan*/ ) ; 
#define  POWER_SUPPLY_PROP_CAPACITY 132 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 128 
 void* POWER_SUPPLY_TECHNOLOGY_LION ; 
 struct goldfish_battery_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int goldfish_battery_get_property(struct power_supply *psy,
				 enum power_supply_property psp,
				 union power_supply_propval *val)
{
	struct goldfish_battery_data *data = power_supply_get_drvdata(psy);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_STATUS);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_HEALTH);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_PRESENT);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CAPACITY);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}