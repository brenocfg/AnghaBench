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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_core_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi5_core_init(struct platform_device *pdev, struct hdmi_core_data *core)
{
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "core");
	if (!res) {
		DSSERR("can't get CORE IORESOURCE_MEM HDMI\n");
		return -EINVAL;
	}

	core->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(core->base)) {
		DSSERR("can't ioremap HDMI core\n");
		return PTR_ERR(core->base);
	}

	return 0;
}