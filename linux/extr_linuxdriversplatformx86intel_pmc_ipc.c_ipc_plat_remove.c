#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/  telemetry_dev; int /*<<< orphan*/  punit_dev; int /*<<< orphan*/  tco_dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ipc_group ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipc_plat_remove(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &intel_ipc_group);
	devm_free_irq(&pdev->dev, ipcdev.irq, &ipcdev);
	platform_device_unregister(ipcdev.tco_dev);
	platform_device_unregister(ipcdev.punit_dev);
	platform_device_unregister(ipcdev.telemetry_dev);
	ipcdev.dev = NULL;
	return 0;
}