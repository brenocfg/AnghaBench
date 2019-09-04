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
struct power_supply_info {int /*<<< orphan*/  use_for_apm; int /*<<< orphan*/  name; } ;
struct power_supply_desc {int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  get_property; int /*<<< orphan*/  type; int /*<<< orphan*/  use_for_apm; int /*<<< orphan*/  name; } ;
struct da9030_charger {struct power_supply_info* battery_info; struct power_supply_desc psy_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int /*<<< orphan*/  da9030_battery_get_property ; 
 int /*<<< orphan*/  da9030_battery_props ; 

__attribute__((used)) static void da9030_battery_setup_psy(struct da9030_charger *charger)
{
	struct power_supply_desc *psy_desc = &charger->psy_desc;
	struct power_supply_info *info = charger->battery_info;

	psy_desc->name = info->name;
	psy_desc->use_for_apm = info->use_for_apm;
	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->get_property = da9030_battery_get_property;

	psy_desc->properties = da9030_battery_props;
	psy_desc->num_properties = ARRAY_SIZE(da9030_battery_props);
}