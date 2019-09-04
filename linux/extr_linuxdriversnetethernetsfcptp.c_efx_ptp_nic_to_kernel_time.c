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
struct efx_tx_queue {int /*<<< orphan*/  completed_timestamp_minor; int /*<<< orphan*/  completed_timestamp_major; struct efx_nic* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  general_tx; } ;
struct efx_ptp_data {TYPE_1__ ts_corrections; int /*<<< orphan*/  (* nic_to_kernel_time ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  efx_ptp_mac_nic_to_ktime_correction (struct efx_nic*,struct efx_ptp_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ efx_ptp_use_mac_tx_timestamps (struct efx_nic*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ktime_t efx_ptp_nic_to_kernel_time(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;
	struct efx_ptp_data *ptp = efx->ptp_data;
	ktime_t kt;

	if (efx_ptp_use_mac_tx_timestamps(efx))
		kt = efx_ptp_mac_nic_to_ktime_correction(efx, ptp,
				tx_queue->completed_timestamp_major,
				tx_queue->completed_timestamp_minor,
				ptp->ts_corrections.general_tx);
	else
		kt = ptp->nic_to_kernel_time(
				tx_queue->completed_timestamp_major,
				tx_queue->completed_timestamp_minor,
				ptp->ts_corrections.general_tx);
	return kt;
}