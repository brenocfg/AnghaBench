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
struct power_supply_desc {int /*<<< orphan*/ * external_power_changed; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int /*<<< orphan*/  ds278x_battery_get_property ; 
 int /*<<< orphan*/  ds278x_battery_props ; 

__attribute__((used)) static void ds278x_power_supply_init(struct power_supply_desc *battery)
{
	battery->type			= POWER_SUPPLY_TYPE_BATTERY;
	battery->properties		= ds278x_battery_props;
	battery->num_properties		= ARRAY_SIZE(ds278x_battery_props);
	battery->get_property		= ds278x_battery_get_property;
	battery->external_power_changed	= NULL;
}