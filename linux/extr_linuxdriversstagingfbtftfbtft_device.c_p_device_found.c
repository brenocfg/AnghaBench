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
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int p_device_found(struct device *dev, void *data)
{
	struct platform_device
	*pdev = to_platform_device(dev);

	if (strstr(pdev->name, "fb"))
		dev_info(dev, "%s id=%d pdata? %s\n", pdev->name, pdev->id,
			 pdev->dev.platform_data ? "yes" : "no");

	return 0;
}