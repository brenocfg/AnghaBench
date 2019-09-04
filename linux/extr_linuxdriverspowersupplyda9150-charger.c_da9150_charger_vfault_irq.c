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
struct da9150_charger {int /*<<< orphan*/  battery; int /*<<< orphan*/  usb; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t da9150_charger_vfault_irq(int irq, void *data)
{
	struct da9150_charger *charger = data;

	/* Nothing we can really do except report this. */
	dev_crit(charger->dev, "VSYS under voltage!!!\n");
	power_supply_changed(charger->usb);
	power_supply_changed(charger->battery);

	return IRQ_HANDLED;
}