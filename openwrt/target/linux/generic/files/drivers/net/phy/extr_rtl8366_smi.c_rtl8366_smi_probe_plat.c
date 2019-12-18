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
struct rtl8366_smi {int /*<<< orphan*/  hw_reset; int /*<<< orphan*/  gpio_sck; int /*<<< orphan*/  gpio_sda; } ;
struct rtl8366_platform_data {int /*<<< orphan*/  hw_reset; int /*<<< orphan*/  gpio_sck; int /*<<< orphan*/  gpio_sda; } ;
struct TYPE_2__ {struct rtl8366_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 

int rtl8366_smi_probe_plat(struct platform_device *pdev, struct rtl8366_smi *smi)
{
	struct rtl8366_platform_data *pdata = pdev->dev.platform_data;

	if (!pdev->dev.platform_data) {
		dev_err(&pdev->dev, "no platform data specified\n");
		return -EINVAL;
	}

	smi->gpio_sda = pdata->gpio_sda;
	smi->gpio_sck = pdata->gpio_sck;
	smi->hw_reset = pdata->hw_reset;

	return 0;
}