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
struct efx_ef10_nic_data {int /*<<< orphan*/  udp_tunnels_lock; scalar_t__ udp_tunnels_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_device_detach_sync (struct efx_nic*) ; 
 int efx_ef10_set_udp_tnl_ports (struct efx_nic*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_udp_tnl_push_ports(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	int rc = 0;

	mutex_lock(&nic_data->udp_tunnels_lock);
	if (nic_data->udp_tunnels_dirty) {
		/* Make sure all TX are stopped while we modify the table, else
		 * we might race against an efx_features_check().
		 */
		efx_device_detach_sync(efx);
		rc = efx_ef10_set_udp_tnl_ports(efx, false);
	}
	mutex_unlock(&nic_data->udp_tunnels_lock);
	return rc;
}