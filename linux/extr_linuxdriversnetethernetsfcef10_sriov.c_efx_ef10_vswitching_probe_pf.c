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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct efx_nic {int /*<<< orphan*/  pci_dev; struct net_device* net_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  vport_id; int /*<<< orphan*/  vport_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EF10_NO_VLAN ; 
 int /*<<< orphan*/  EVB_PORT_ID_ASSIGNED ; 
 int /*<<< orphan*/  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL ; 
 int /*<<< orphan*/  MC_CMD_VSWITCH_ALLOC_IN_VSWITCH_TYPE_VEB ; 
 int efx_ef10_vadaptor_alloc_set_features (struct efx_nic*) ; 
 int efx_ef10_vport_add_mac (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_ef10_vport_alloc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ef10_vport_del_mac (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_vport_free (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_ef10_vswitch_alloc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_vswitch_free (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 

int efx_ef10_vswitching_probe_pf(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	struct net_device *net_dev = efx->net_dev;
	int rc;

	if (pci_sriov_get_totalvfs(efx->pci_dev) <= 0) {
		/* vswitch not needed as we have no VFs */
		efx_ef10_vadaptor_alloc_set_features(efx);
		return 0;
	}

	rc = efx_ef10_vswitch_alloc(efx, EVB_PORT_ID_ASSIGNED,
				    MC_CMD_VSWITCH_ALLOC_IN_VSWITCH_TYPE_VEB);
	if (rc)
		goto fail1;

	rc = efx_ef10_vport_alloc(efx, EVB_PORT_ID_ASSIGNED,
				  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL,
				  EFX_EF10_NO_VLAN, &nic_data->vport_id);
	if (rc)
		goto fail2;

	rc = efx_ef10_vport_add_mac(efx, nic_data->vport_id, net_dev->dev_addr);
	if (rc)
		goto fail3;
	ether_addr_copy(nic_data->vport_mac, net_dev->dev_addr);

	rc = efx_ef10_vadaptor_alloc_set_features(efx);
	if (rc)
		goto fail4;

	return 0;
fail4:
	efx_ef10_vport_del_mac(efx, nic_data->vport_id, nic_data->vport_mac);
	eth_zero_addr(nic_data->vport_mac);
fail3:
	efx_ef10_vport_free(efx, nic_data->vport_id);
	nic_data->vport_id = EVB_PORT_ID_ASSIGNED;
fail2:
	efx_ef10_vswitch_free(efx, EVB_PORT_ID_ASSIGNED);
fail1:
	return rc;
}