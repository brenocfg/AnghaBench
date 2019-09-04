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
struct pci_dev {int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEV_FLAGS_BRIDGE_XLATE_ROOT ; 

__attribute__((used)) static void quirk_bridge_cavm_thrx2_pcie_root(struct pci_dev *pdev)
{
	pdev->dev_flags |= PCI_DEV_FLAGS_BRIDGE_XLATE_ROOT;
}