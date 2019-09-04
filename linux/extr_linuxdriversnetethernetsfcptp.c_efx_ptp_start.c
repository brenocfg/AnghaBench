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
struct efx_ptp_data {int reset_required; scalar_t__ current_adjfreq; scalar_t__ evt_frag_idx; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;

/* Variables and functions */
 int efx_ptp_enable (struct efx_nic*) ; 
 int efx_ptp_insert_multicast_filters (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ptp_remove_multicast_filters (struct efx_nic*) ; 

__attribute__((used)) static int efx_ptp_start(struct efx_nic *efx)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	int rc;

	ptp->reset_required = false;

	rc = efx_ptp_insert_multicast_filters(efx);
	if (rc)
		return rc;

	rc = efx_ptp_enable(efx);
	if (rc != 0)
		goto fail;

	ptp->evt_frag_idx = 0;
	ptp->current_adjfreq = 0;

	return 0;

fail:
	efx_ptp_remove_multicast_filters(efx);
	return rc;
}