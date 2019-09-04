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
struct TYPE_2__ {struct z2_charger* properties; } ;
struct z2_charger {TYPE_1__ batt_ps_desc; int /*<<< orphan*/  batt_ps; int /*<<< orphan*/  bat_work; struct z2_battery_info* info; } ;
struct z2_battery_info {scalar_t__ charge_gpio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct z2_charger*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 scalar_t__ gpio_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  gpio_to_irq (scalar_t__) ; 
 struct z2_charger* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct z2_charger*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int z2_batt_remove(struct i2c_client *client)
{
	struct z2_charger *charger = i2c_get_clientdata(client);
	struct z2_battery_info *info = charger->info;

	cancel_work_sync(&charger->bat_work);
	power_supply_unregister(charger->batt_ps);

	kfree(charger->batt_ps_desc.properties);
	if (info->charge_gpio >= 0 && gpio_is_valid(info->charge_gpio)) {
		free_irq(gpio_to_irq(info->charge_gpio), charger);
		gpio_free(info->charge_gpio);
	}

	kfree(charger);

	return 0;
}