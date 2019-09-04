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
struct pps_gpio_device_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  pps; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct pps_gpio_device_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pps_unregister_source (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pps_gpio_remove(struct platform_device *pdev)
{
	struct pps_gpio_device_data *data = platform_get_drvdata(pdev);

	pps_unregister_source(data->pps);
	dev_info(&pdev->dev, "removed IRQ %d as PPS source\n", data->irq);
	return 0;
}