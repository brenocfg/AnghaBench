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
union power_supply_propval {int /*<<< orphan*/  strval; } ;
struct gb_power_supply {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  model_name; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
#define  POWER_SUPPLY_PROP_MANUFACTURER 130 
#define  POWER_SUPPLY_PROP_MODEL_NAME 129 
#define  POWER_SUPPLY_PROP_SERIAL_NUMBER 128 

__attribute__((used)) static int __gb_power_supply_property_strval_get(struct gb_power_supply *gbpsy,
						enum power_supply_property psp,
						union power_supply_propval *val)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = gbpsy->model_name;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = gbpsy->manufacturer;
		break;
	case POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = gbpsy->serial_number;
		break;
	default:
		break;
	}

	return 0;
}