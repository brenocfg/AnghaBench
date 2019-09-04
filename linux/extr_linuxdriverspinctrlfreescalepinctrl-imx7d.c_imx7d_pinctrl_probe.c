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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct imx_pinctrl_soc_info {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int imx_pinctrl_probe (struct platform_device*,struct imx_pinctrl_soc_info const*) ; 
 struct imx_pinctrl_soc_info* of_device_get_match_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx7d_pinctrl_probe(struct platform_device *pdev)
{
	const struct imx_pinctrl_soc_info *pinctrl_info;

	pinctrl_info = of_device_get_match_data(&pdev->dev);
	if (!pinctrl_info)
		return -ENODEV;

	return imx_pinctrl_probe(pdev, pinctrl_info);
}