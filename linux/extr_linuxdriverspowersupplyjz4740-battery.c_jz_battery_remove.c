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
struct platform_device {int dummy; } ;
struct jz_battery {scalar_t__ charge_irq; scalar_t__ irq; int /*<<< orphan*/  battery; TYPE_1__* pdata; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_charge; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct jz_battery*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct jz_battery* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz_battery_remove(struct platform_device *pdev)
{
	struct jz_battery *jz_battery = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&jz_battery->work);

	if (gpio_is_valid(jz_battery->pdata->gpio_charge)) {
		if (jz_battery->charge_irq >= 0)
			free_irq(jz_battery->charge_irq, jz_battery);
		gpio_free(jz_battery->pdata->gpio_charge);
	}

	power_supply_unregister(jz_battery->battery);

	free_irq(jz_battery->irq, jz_battery);

	return 0;
}