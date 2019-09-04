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
struct pm860x_charger_info {int irq_nums; int /*<<< orphan*/ * irq; int /*<<< orphan*/  usb; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pm860x_charger_info*) ; 
 struct pm860x_charger_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_charger_remove(struct platform_device *pdev)
{
	struct pm860x_charger_info *info = platform_get_drvdata(pdev);
	int i;

	power_supply_unregister(info->usb);
	for (i = 0; i < info->irq_nums; i++)
		free_irq(info->irq[i], info);
	return 0;
}