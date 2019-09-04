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
struct efx_nic {int /*<<< orphan*/  filter_sem; scalar_t__ filter_state; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_vlan {int /*<<< orphan*/  list; int /*<<< orphan*/  vid; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  vlan_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ef10_filter_del_vlan (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct efx_ef10_vlan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_ef10_del_vlan_internal(struct efx_nic *efx,
				       struct efx_ef10_vlan *vlan)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	WARN_ON(!mutex_is_locked(&nic_data->vlan_lock));

	if (efx->filter_state) {
		down_write(&efx->filter_sem);
		efx_ef10_filter_del_vlan(efx, vlan->vid);
		up_write(&efx->filter_sem);
	}

	list_del(&vlan->list);
	kfree(vlan);
}