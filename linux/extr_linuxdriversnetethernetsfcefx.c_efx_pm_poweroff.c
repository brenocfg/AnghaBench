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
struct pci_dev {int dummy; } ;
struct efx_nic {scalar_t__ reset_pending; TYPE_1__* type; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 struct efx_nic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int efx_pm_poweroff(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	struct efx_nic *efx = pci_get_drvdata(pci_dev);

	efx->type->fini(efx);

	efx->reset_pending = 0;

	pci_save_state(pci_dev);
	return pci_set_power_state(pci_dev, PCI_D3hot);
}