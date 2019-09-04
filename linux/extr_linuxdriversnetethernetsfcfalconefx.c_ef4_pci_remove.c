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
struct ef4_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_UNINIT ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_disable_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_dissociate (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_fini_io (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_fini_struct (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_mtd_remove (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_pci_remove_main (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_unregister_netdev (struct ef4_nic*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct ef4_nic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void ef4_pci_remove(struct pci_dev *pci_dev)
{
	struct ef4_nic *efx;

	efx = pci_get_drvdata(pci_dev);
	if (!efx)
		return;

	/* Mark the NIC as fini, then stop the interface */
	rtnl_lock();
	ef4_dissociate(efx);
	dev_close(efx->net_dev);
	ef4_disable_interrupts(efx);
	efx->state = STATE_UNINIT;
	rtnl_unlock();

	ef4_unregister_netdev(efx);

	ef4_mtd_remove(efx);

	ef4_pci_remove_main(efx);

	ef4_fini_io(efx);
	netif_dbg(efx, drv, efx->net_dev, "shutdown successful\n");

	ef4_fini_struct(efx);
	free_netdev(efx->net_dev);

	pci_disable_pcie_error_reporting(pci_dev);
}