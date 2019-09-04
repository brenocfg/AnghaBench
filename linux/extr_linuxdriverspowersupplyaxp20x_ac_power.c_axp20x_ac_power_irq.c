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
struct axp20x_ac_power {int /*<<< orphan*/  supply; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t axp20x_ac_power_irq(int irq, void *devid)
{
	struct axp20x_ac_power *power = devid;

	power_supply_changed(power->supply);

	return IRQ_HANDLED;
}