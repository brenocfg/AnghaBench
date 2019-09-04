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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct idt_ntb_dev {TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idt_deinit_pci(struct idt_ntb_dev *ndev)
{
	struct pci_dev *pdev = ndev->ntb.pdev;

	/* Clean up the PCI-device private data pointer */
	pci_set_drvdata(pdev, NULL);

	/* Clear the bus master disabling the Request TLPs translation */
	pci_clear_master(pdev);

	/* Disable the AER capability */
	(void)pci_disable_pcie_error_reporting(pdev);

	dev_dbg(&pdev->dev, "NT-function PCIe interface cleared");
}