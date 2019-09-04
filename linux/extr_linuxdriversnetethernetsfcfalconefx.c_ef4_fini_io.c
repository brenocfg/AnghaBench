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
struct ef4_nic {int /*<<< orphan*/  pci_dev; scalar_t__ membase_phys; TYPE_1__* type; int /*<<< orphan*/ * membase; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int mem_bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_vfs_assigned (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ef4_fini_io(struct ef4_nic *efx)
{
	int bar;

	netif_dbg(efx, drv, efx->net_dev, "shutting down I/O\n");

	if (efx->membase) {
		iounmap(efx->membase);
		efx->membase = NULL;
	}

	if (efx->membase_phys) {
		bar = efx->type->mem_bar;
		pci_release_region(efx->pci_dev, bar);
		efx->membase_phys = 0;
	}

	/* Don't disable bus-mastering if VFs are assigned */
	if (!pci_vfs_assigned(efx->pci_dev))
		pci_disable_device(efx->pci_dev);
}