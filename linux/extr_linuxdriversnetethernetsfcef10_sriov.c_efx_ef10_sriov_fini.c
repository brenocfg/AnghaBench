#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {unsigned int vf_count; int /*<<< orphan*/  net_dev; TYPE_3__* pci_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {TYPE_1__* vf; } ;
struct TYPE_9__ {TYPE_2__* driver; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* remove ) (TYPE_3__*) ;} ;
struct TYPE_7__ {struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int efx_ef10_pci_sriov_disable (struct efx_nic*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pci_disable_sriov (TYPE_3__*) ; 
 scalar_t__ pci_num_vf (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void efx_ef10_sriov_fini(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	unsigned int i;
	int rc;

	if (!nic_data->vf) {
		/* Remove any un-assigned orphaned VFs */
		if (pci_num_vf(efx->pci_dev) && !pci_vfs_assigned(efx->pci_dev))
			pci_disable_sriov(efx->pci_dev);
		return;
	}

	/* Remove any VFs in the host */
	for (i = 0; i < efx->vf_count; ++i) {
		struct efx_nic *vf_efx = nic_data->vf[i].efx;

		if (vf_efx)
			vf_efx->pci_dev->driver->remove(vf_efx->pci_dev);
	}

	rc = efx_ef10_pci_sriov_disable(efx, true);
	if (rc)
		netif_dbg(efx, drv, efx->net_dev,
			  "Disabling SRIOV was not successful rc=%d\n", rc);
	else
		netif_dbg(efx, drv, efx->net_dev, "SRIOV disabled\n");
}