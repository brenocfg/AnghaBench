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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ci_hdrc {TYPE_1__* dev; scalar_t__ supports_runtime_pm; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_attr_group ; 
 int /*<<< orphan*/  ci_hdrc_enter_lpm (struct ci_hdrc*,int) ; 
 int /*<<< orphan*/  ci_role_destroy (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_ulpi_exit (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_usb_phy_exit (struct ci_hdrc*) ; 
 int /*<<< orphan*/  dbg_remove_files (struct ci_hdrc*) ; 
 struct ci_hdrc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ci_hdrc_remove(struct platform_device *pdev)
{
	struct ci_hdrc *ci = platform_get_drvdata(pdev);

	if (ci->supports_runtime_pm) {
		pm_runtime_get_sync(&pdev->dev);
		pm_runtime_disable(&pdev->dev);
		pm_runtime_put_noidle(&pdev->dev);
	}

	dbg_remove_files(ci);
	sysfs_remove_group(&ci->dev->kobj, &ci_attr_group);
	ci_role_destroy(ci);
	ci_hdrc_enter_lpm(ci, true);
	ci_usb_phy_exit(ci);
	ci_ulpi_exit(ci);

	return 0;
}