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
struct wil6210_priv {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  wil6210_fini_irq (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 

__attribute__((used)) static int wil_if_pcie_disable(struct wil6210_priv *wil)
{
	struct pci_dev *pdev = wil->pdev;

	wil_dbg_misc(wil, "if_pcie_disable\n");

	pci_clear_master(pdev);
	/* disable and release IRQ */
	wil6210_fini_irq(wil, pdev->irq);
	/* safe to call if no MSI */
	pci_disable_msi(pdev);
	/* TODO: disable HW */

	return 0;
}