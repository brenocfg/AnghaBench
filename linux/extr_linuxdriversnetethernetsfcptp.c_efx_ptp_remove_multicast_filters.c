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
struct efx_ptp_data {int rxfilter_installed; int /*<<< orphan*/  rxfilter_event; int /*<<< orphan*/  rxfilter_general; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_PRI_REQUIRED ; 
 int /*<<< orphan*/  efx_filter_remove_id_safe (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ptp_remove_multicast_filters(struct efx_nic *efx)
{
	struct efx_ptp_data *ptp = efx->ptp_data;

	if (ptp->rxfilter_installed) {
		efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  ptp->rxfilter_general);
		efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  ptp->rxfilter_event);
		ptp->rxfilter_installed = false;
	}
}