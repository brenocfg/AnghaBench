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
struct jz_battery {int status; long voltage; int /*<<< orphan*/  battery; TYPE_1__* pdata; } ;
struct TYPE_2__ {int gpio_charge_active_low; int /*<<< orphan*/  gpio_charge; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int abs (long) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 long jz_battery_read_voltage (struct jz_battery*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz_battery_update(struct jz_battery *jz_battery)
{
	int status;
	long voltage;
	bool has_changed = false;
	int is_charging;

	if (gpio_is_valid(jz_battery->pdata->gpio_charge)) {
		is_charging = gpio_get_value(jz_battery->pdata->gpio_charge);
		is_charging ^= jz_battery->pdata->gpio_charge_active_low;
		if (is_charging)
			status = POWER_SUPPLY_STATUS_CHARGING;
		else
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;

		if (status != jz_battery->status) {
			jz_battery->status = status;
			has_changed = true;
		}
	}

	voltage = jz_battery_read_voltage(jz_battery);
	if (voltage >= 0 && abs(voltage - jz_battery->voltage) > 50000) {
		jz_battery->voltage = voltage;
		has_changed = true;
	}

	if (has_changed)
		power_supply_changed(jz_battery->battery);
}