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
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int datapath_caps; scalar_t__ udp_tunnels_dirty; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN ; 
 int /*<<< orphan*/ * __efx_ef10_udp_tnl_lookup_port (struct efx_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool efx_ef10_udp_tnl_has_port(struct efx_nic *efx, __be16 port)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	if (!(nic_data->datapath_caps &
	      (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN)))
		return false;

	if (nic_data->udp_tunnels_dirty)
		/* SW table may not match HW state, so just assume we can't
		 * use any UDP tunnel offloads.
		 */
		return false;

	return __efx_ef10_udp_tnl_lookup_port(efx, port) != NULL;
}