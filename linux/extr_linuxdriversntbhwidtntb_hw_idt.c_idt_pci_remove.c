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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct idt_ntb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idt_deinit_dbgfs (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_deinit_isr (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_deinit_link (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_deinit_pci (struct idt_ntb_dev*) ; 
 int /*<<< orphan*/  idt_unregister_device (struct idt_ntb_dev*) ; 
 struct idt_ntb_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void idt_pci_remove(struct pci_dev *pdev)
{
	struct idt_ntb_dev *ndev = pci_get_drvdata(pdev);

	/* Deinit the DebugFS node */
	idt_deinit_dbgfs(ndev);

	/* Unregister NTB device */
	idt_unregister_device(ndev);

	/* Stop the interrupts handling */
	idt_deinit_isr(ndev);

	/* Deinitialize link event subsystem */
	idt_deinit_link(ndev);

	/* Deinit basic PCI subsystem */
	idt_deinit_pci(ndev);

	/* IDT PCIe-switch NTB driver is finally initialized */
	dev_info(&pdev->dev, "IDT NTB device is removed");

	/* Sayonara... */
}