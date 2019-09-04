#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* olpc_ac ; 
 TYPE_1__* olpc_bat ; 
 int /*<<< orphan*/  olpc_bat_eeprom ; 
 int /*<<< orphan*/  olpc_bat_error ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_1__*) ; 

__attribute__((used)) static int olpc_battery_remove(struct platform_device *pdev)
{
	device_remove_file(&olpc_bat->dev, &olpc_bat_error);
	device_remove_bin_file(&olpc_bat->dev, &olpc_bat_eeprom);
	power_supply_unregister(olpc_bat);
	power_supply_unregister(olpc_ac);
	return 0;
}