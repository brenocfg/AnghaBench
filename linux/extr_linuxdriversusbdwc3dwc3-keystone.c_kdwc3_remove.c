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
struct dwc3_keystone {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdwc3_disable_irqs (struct dwc3_keystone*) ; 
 int /*<<< orphan*/  kdwc3_remove_core ; 
 struct dwc3_keystone* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdwc3_remove(struct platform_device *pdev)
{
	struct dwc3_keystone *kdwc = platform_get_drvdata(pdev);

	kdwc3_disable_irqs(kdwc);
	device_for_each_child(&pdev->dev, NULL, kdwc3_remove_core);
	pm_runtime_put_sync(kdwc->dev);
	pm_runtime_disable(kdwc->dev);

	platform_set_drvdata(pdev, NULL);

	return 0;
}