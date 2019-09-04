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
typedef  int u32 ;
struct efx_nic {int /*<<< orphan*/  fixed_features; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  vport_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVB_PORT_ID_ASSIGNED ; 
 int MC_CMD_VPORT_ALLOC_IN_FLAG_VLAN_RESTRICT_LBN ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int efx_ef10_vadaptor_alloc (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_vadaptor_free (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_ef10_vadaptor_query (struct efx_nic*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_vadaptor_alloc_set_features(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 port_flags;
	int rc;

	rc = efx_ef10_vadaptor_alloc(efx, nic_data->vport_id);
	if (rc)
		goto fail_vadaptor_alloc;

	rc = efx_ef10_vadaptor_query(efx, nic_data->vport_id,
				     &port_flags, NULL, NULL);
	if (rc)
		goto fail_vadaptor_query;

	if (port_flags &
	    (1 << MC_CMD_VPORT_ALLOC_IN_FLAG_VLAN_RESTRICT_LBN))
		efx->fixed_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	else
		efx->fixed_features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;

	return 0;

fail_vadaptor_query:
	efx_ef10_vadaptor_free(efx, EVB_PORT_ID_ASSIGNED);
fail_vadaptor_alloc:
	return rc;
}