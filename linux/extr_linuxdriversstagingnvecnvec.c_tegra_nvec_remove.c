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
struct platform_device {int dummy; } ;
struct nvec_chip {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  nvec_status_notifier; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvec_toggle_global_events (struct nvec_chip*,int) ; 
 int /*<<< orphan*/  nvec_unregister_notifier (struct nvec_chip*,int /*<<< orphan*/ *) ; 
 struct nvec_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * pm_power_off ; 

__attribute__((used)) static int tegra_nvec_remove(struct platform_device *pdev)
{
	struct nvec_chip *nvec = platform_get_drvdata(pdev);

	nvec_toggle_global_events(nvec, false);
	mfd_remove_devices(nvec->dev);
	nvec_unregister_notifier(nvec, &nvec->nvec_status_notifier);
	cancel_work_sync(&nvec->rx_work);
	cancel_work_sync(&nvec->tx_work);
	/* FIXME: needs check whether nvec is responsible for power off */
	pm_power_off = NULL;

	return 0;
}