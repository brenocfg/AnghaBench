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
struct pci_dev {int dummy; } ;
struct acp3x_dev_data {int /*<<< orphan*/  acp3x_base; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct acp3x_dev_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_acp3x_remove(struct pci_dev *pci)
{
	struct acp3x_dev_data *adata = pci_get_drvdata(pci);

	platform_device_unregister(adata->pdev);
	iounmap(adata->acp3x_base);

	pci_disable_msi(pci);
	pci_release_regions(pci);
	pci_disable_device(pci);
}