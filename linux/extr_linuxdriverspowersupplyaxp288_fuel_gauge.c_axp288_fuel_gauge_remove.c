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
struct axp288_fg_info {scalar_t__* irq; int /*<<< orphan*/ * iio_channel; int /*<<< orphan*/  bat; } ;

/* Variables and functions */
 int AXP288_FG_INTR_NUM ; 
 int IIO_CHANNEL_NUM ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct axp288_fg_info*) ; 
 int /*<<< orphan*/  fuel_gauge_remove_debugfs (struct axp288_fg_info*) ; 
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 struct axp288_fg_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp288_fuel_gauge_remove(struct platform_device *pdev)
{
	struct axp288_fg_info *info = platform_get_drvdata(pdev);
	int i;

	power_supply_unregister(info->bat);
	fuel_gauge_remove_debugfs(info);

	for (i = 0; i < AXP288_FG_INTR_NUM; i++)
		if (info->irq[i] >= 0)
			free_irq(info->irq[i], info);

	for (i = 0; i < IIO_CHANNEL_NUM; i++)
		iio_channel_release(info->iio_channel[i]);

	return 0;
}