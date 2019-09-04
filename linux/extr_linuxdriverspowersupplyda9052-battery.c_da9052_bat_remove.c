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
struct platform_device {int dummy; } ;
struct da9052_battery {int /*<<< orphan*/  psy; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * da9052_bat_irq_bits ; 
 int /*<<< orphan*/  da9052_bat_irqs ; 
 int /*<<< orphan*/  da9052_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_battery*) ; 
 struct da9052_battery* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9052_bat_remove(struct platform_device *pdev)
{
	int i;
	struct da9052_battery *bat = platform_get_drvdata(pdev);

	for (i = 0; i < ARRAY_SIZE(da9052_bat_irqs); i++)
		da9052_free_irq(bat->da9052, da9052_bat_irq_bits[i], bat);

	power_supply_unregister(bat->psy);

	return 0;
}