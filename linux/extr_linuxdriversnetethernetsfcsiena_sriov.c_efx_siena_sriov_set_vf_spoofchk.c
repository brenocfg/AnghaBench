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
struct siena_vf {scalar_t__ txq_count; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  tx_filter_mode; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {int vf_init_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VF_TX_FILTER_OFF ; 
 int /*<<< orphan*/  VF_TX_FILTER_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int efx_siena_sriov_set_vf_spoofchk(struct efx_nic *efx, int vf_i,
				    bool spoofchk)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	struct siena_vf *vf;
	int rc;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->txq_lock);
	if (vf->txq_count == 0) {
		vf->tx_filter_mode =
			spoofchk ? VF_TX_FILTER_ON : VF_TX_FILTER_OFF;
		rc = 0;
	} else {
		/* This cannot be changed while TX queues are running */
		rc = -EBUSY;
	}
	mutex_unlock(&vf->txq_lock);
	return rc;
}