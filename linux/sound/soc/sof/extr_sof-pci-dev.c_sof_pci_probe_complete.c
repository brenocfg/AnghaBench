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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOF_SUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  pm_runtime_allow (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

__attribute__((used)) static void sof_pci_probe_complete(struct device *dev)
{
	dev_dbg(dev, "Completing SOF PCI probe");

	/* allow runtime_pm */
	pm_runtime_set_autosuspend_delay(dev, SND_SOF_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(dev);

	/*
	 * runtime pm for pci device is "forbidden" by default.
	 * so call pm_runtime_allow() to enable it.
	 */
	pm_runtime_allow(dev);

	/* mark last_busy for pm_runtime to make sure not suspend immediately */
	pm_runtime_mark_last_busy(dev);

	/* follow recommendation in pci-driver.c to decrement usage counter */
	pm_runtime_put_noidle(dev);
}