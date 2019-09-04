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
struct power_supply {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ device_add_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tpacpi_battery_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpacpi_battery_groups ; 
 scalar_t__ tpacpi_battery_probe (int) ; 

__attribute__((used)) static int tpacpi_battery_add(struct power_supply *battery)
{
	int batteryid = tpacpi_battery_get_id(battery->desc->name);

	if (tpacpi_battery_probe(batteryid))
		return -ENODEV;
	if (device_add_groups(&battery->dev, tpacpi_battery_groups))
		return -ENODEV;
	return 0;
}