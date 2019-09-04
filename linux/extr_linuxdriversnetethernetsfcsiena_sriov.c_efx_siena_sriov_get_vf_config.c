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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tci; int /*<<< orphan*/  mac_addr; } ;
struct siena_vf {scalar_t__ tx_filter_mode; TYPE_1__ addr; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct ifla_vf_info {int vf; int vlan; int qos; int spoofchk; scalar_t__ min_tx_rate; scalar_t__ max_tx_rate; int /*<<< orphan*/  mac; } ;
struct efx_nic {int vf_init_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VF_TX_FILTER_ON ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

int efx_siena_sriov_get_vf_config(struct efx_nic *efx, int vf_i,
				  struct ifla_vf_info *ivi)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	struct siena_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = nic_data->vf + vf_i;

	ivi->vf = vf_i;
	ether_addr_copy(ivi->mac, vf->addr.mac_addr);
	ivi->max_tx_rate = 0;
	ivi->min_tx_rate = 0;
	tci = ntohs(vf->addr.tci);
	ivi->vlan = tci & VLAN_VID_MASK;
	ivi->qos = (tci >> VLAN_PRIO_SHIFT) & 0x7;
	ivi->spoofchk = vf->tx_filter_mode == VF_TX_FILTER_ON;

	return 0;
}