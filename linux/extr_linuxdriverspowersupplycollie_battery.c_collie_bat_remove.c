#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ucb1x00_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  psy; } ;
struct TYPE_4__ {int /*<<< orphan*/  psy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLLIE_GPIO_CO ; 
 int /*<<< orphan*/  bat_work ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_3__ collie_bat_bu ; 
 TYPE_1__ collie_bat_main ; 
 int /*<<< orphan*/  collie_batt_gpios ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collie_bat_remove(struct ucb1x00_dev *dev)
{
	free_irq(gpio_to_irq(COLLIE_GPIO_CO), &collie_bat_main);

	power_supply_unregister(collie_bat_bu.psy);
	power_supply_unregister(collie_bat_main.psy);

	/*
	 * Now cancel the bat_work.  We won't get any more schedules,
	 * since all sources (isr and external_power_changed) are
	 * unregistered now.
	 */
	cancel_work_sync(&bat_work);
	gpio_free_array(collie_batt_gpios, ARRAY_SIZE(collie_batt_gpios));
}