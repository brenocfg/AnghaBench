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
struct w1_gpio_platform_data {scalar_t__ pullup_gpiod; int /*<<< orphan*/  (* enable_external_pullup ) (int /*<<< orphan*/ ) ;} ;
struct w1_bus_master {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct w1_gpio_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 struct w1_bus_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_remove_master_device (struct w1_bus_master*) ; 

__attribute__((used)) static int w1_gpio_remove(struct platform_device *pdev)
{
	struct w1_bus_master *master = platform_get_drvdata(pdev);
	struct w1_gpio_platform_data *pdata = dev_get_platdata(&pdev->dev);

	if (pdata->enable_external_pullup)
		pdata->enable_external_pullup(0);

	if (pdata->pullup_gpiod)
		gpiod_set_value(pdata->pullup_gpiod, 0);

	w1_remove_master_device(master);

	return 0;
}