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
struct st_hba {scalar_t__ msi_enabled; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct st_hba*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 

__attribute__((used)) static void stex_free_irq(struct st_hba *hba)
{
	struct pci_dev *pdev = hba->pdev;

	free_irq(pdev->irq, hba);
	if (hba->msi_enabled)
		pci_disable_msi(pdev);
}