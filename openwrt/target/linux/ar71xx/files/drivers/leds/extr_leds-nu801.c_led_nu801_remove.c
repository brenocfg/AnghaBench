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
struct TYPE_2__ {struct led_nu801_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct led_nu801_platform_data {int num_controllers; } ;
struct led_nu801_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct led_nu801_data*) ; 
 int /*<<< orphan*/  led_nu801_delete_chain (struct led_nu801_data*) ; 
 struct led_nu801_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int led_nu801_remove(struct platform_device *pdev)
{
	int i;
	struct led_nu801_platform_data *pdata = pdev->dev.platform_data;
	struct led_nu801_data *controllers;

	controllers = platform_get_drvdata(pdev);

	for (i = 0; i < pdata->num_controllers; i++)
		led_nu801_delete_chain(&controllers[i]);

	kfree(controllers);

	return 0;
}