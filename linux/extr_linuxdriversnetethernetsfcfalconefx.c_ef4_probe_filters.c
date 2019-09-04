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
struct ef4_nic {int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  filter_sem; TYPE_1__* type; int /*<<< orphan*/  filter_lock; } ;
struct TYPE_2__ {int (* filter_table_probe ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ef4_probe_filters(struct ef4_nic *efx)
{
	int rc;

	spin_lock_init(&efx->filter_lock);
	init_rwsem(&efx->filter_sem);
	mutex_lock(&efx->mac_lock);
	down_write(&efx->filter_sem);
	rc = efx->type->filter_table_probe(efx);
	if (rc)
		goto out_unlock;

#ifdef CONFIG_RFS_ACCEL
	if (efx->type->offload_features & NETIF_F_NTUPLE) {
		struct ef4_channel *channel;
		int i, success = 1;

		ef4_for_each_channel(channel, efx) {
			channel->rps_flow_id =
				kcalloc(efx->type->max_rx_ip_filters,
					sizeof(*channel->rps_flow_id),
					GFP_KERNEL);
			if (!channel->rps_flow_id)
				success = 0;
			else
				for (i = 0;
				     i < efx->type->max_rx_ip_filters;
				     ++i)
					channel->rps_flow_id[i] =
						RPS_FLOW_ID_INVALID;
		}

		if (!success) {
			ef4_for_each_channel(channel, efx)
				kfree(channel->rps_flow_id);
			efx->type->filter_table_remove(efx);
			rc = -ENOMEM;
			goto out_unlock;
		}

		efx->rps_expire_index = efx->rps_expire_channel = 0;
	}
#endif
out_unlock:
	up_write(&efx->filter_sem);
	mutex_unlock(&efx->mac_lock);
	return rc;
}