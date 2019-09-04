#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mv_otg {int /*<<< orphan*/  phy; scalar_t__ qwork; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  inputs_attr_group ; 
 int /*<<< orphan*/  mv_otg_disable (struct mv_otg*) ; 
 struct mv_otg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv_otg_remove(struct platform_device *pdev)
{
	struct mv_otg *mvotg = platform_get_drvdata(pdev);

	sysfs_remove_group(&mvotg->pdev->dev.kobj, &inputs_attr_group);

	if (mvotg->qwork) {
		flush_workqueue(mvotg->qwork);
		destroy_workqueue(mvotg->qwork);
	}

	mv_otg_disable(mvotg);

	usb_remove_phy(&mvotg->phy);

	return 0;
}