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
struct efx_nic {TYPE_1__* ptp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  workwq; scalar_t__ phc_clock; int /*<<< orphan*/  pps_workwq; int /*<<< orphan*/  txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  pps_work; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ptp_disable (struct efx_nic*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void efx_ptp_remove(struct efx_nic *efx)
{
	if (!efx->ptp_data)
		return;

	(void)efx_ptp_disable(efx);

	cancel_work_sync(&efx->ptp_data->work);
	cancel_work_sync(&efx->ptp_data->pps_work);

	skb_queue_purge(&efx->ptp_data->rxq);
	skb_queue_purge(&efx->ptp_data->txq);

	if (efx->ptp_data->phc_clock) {
		destroy_workqueue(efx->ptp_data->pps_workwq);
		ptp_clock_unregister(efx->ptp_data->phc_clock);
	}

	destroy_workqueue(efx->ptp_data->workwq);

	efx_nic_free_buffer(efx, &efx->ptp_data->start);
	kfree(efx->ptp_data);
	efx->ptp_data = NULL;
}