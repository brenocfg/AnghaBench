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
struct arche_platform_drvdata {int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  arche_platform_poweroff_seq (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_remove_child ; 
 int /*<<< orphan*/  dev_attr_state ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct arche_platform_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 scalar_t__ usb3613_hub_mode_ctrl (int) ; 

__attribute__((used)) static int arche_platform_remove(struct platform_device *pdev)
{
	struct arche_platform_drvdata *arche_pdata = platform_get_drvdata(pdev);

	unregister_pm_notifier(&arche_pdata->pm_notifier);
	device_remove_file(&pdev->dev, &dev_attr_state);
	device_for_each_child(&pdev->dev, NULL, arche_remove_child);
	arche_platform_poweroff_seq(arche_pdata);

	if (usb3613_hub_mode_ctrl(false))
		dev_warn(arche_pdata->dev, "failed to control hub device\n");
		/* TODO: Should we do anything more here ?? */
	return 0;
}