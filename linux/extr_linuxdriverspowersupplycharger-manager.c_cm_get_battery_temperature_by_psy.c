#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct power_supply {int dummy; } ;
struct charger_manager {TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  psy_fuel_gauge; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_TEMP ; 
 struct power_supply* power_supply_get_by_name (int /*<<< orphan*/ ) ; 
 int power_supply_get_property (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 

__attribute__((used)) static int cm_get_battery_temperature_by_psy(struct charger_manager *cm,
					int *temp)
{
	struct power_supply *fuel_gauge;
	int ret;

	fuel_gauge = power_supply_get_by_name(cm->desc->psy_fuel_gauge);
	if (!fuel_gauge)
		return -ENODEV;

	ret = power_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_TEMP,
				(union power_supply_propval *)temp);
	power_supply_put(fuel_gauge);

	return ret;
}