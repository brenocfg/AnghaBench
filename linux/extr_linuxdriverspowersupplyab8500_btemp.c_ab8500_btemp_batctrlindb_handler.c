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
struct TYPE_2__ {int batt_rem; } ;
struct ab8500_btemp {int /*<<< orphan*/  btemp_psy; TYPE_1__ events; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ab8500_btemp_batctrlindb_handler(int irq, void *_di)
{
	struct ab8500_btemp *di = _di;
	dev_err(di->dev, "Battery removal detected!\n");

	di->events.batt_rem = true;
	power_supply_changed(di->btemp_psy);

	return IRQ_HANDLED;
}