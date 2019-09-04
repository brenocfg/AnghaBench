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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct siena_vf {int /*<<< orphan*/  status_lock; TYPE_1__ addr; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {int vf_init_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __efx_siena_sriov_update_vf_addr (struct siena_vf*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int efx_siena_sriov_set_vf_mac(struct efx_nic *efx, int vf_i, u8 *mac)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	struct siena_vf *vf;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->status_lock);
	ether_addr_copy(vf->addr.mac_addr, mac);
	__efx_siena_sriov_update_vf_addr(vf);
	mutex_unlock(&vf->status_lock);

	return 0;
}