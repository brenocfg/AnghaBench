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
struct pci_dev {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEV_FLAGS_NO_PM_RESET ; 
 int /*<<< orphan*/  pci_is_root_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quirk_no_pm_reset(struct pci_dev *dev)
{
	/*
	 * We can't do a bus reset on root bus devices, but an ineffective
	 * PM reset may be better than nothing.
	 */
	if (!pci_is_root_bus(dev->bus))
		dev->dev_flags |= PCI_DEV_FLAGS_NO_PM_RESET;
}