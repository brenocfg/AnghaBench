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
struct hwtstamp_config {int rx_filter; int /*<<< orphan*/  tx_type; } ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 142 
#define  HWTSTAMP_FILTER_NONE 141 
#define  HWTSTAMP_FILTER_NTP_ALL 140 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 137 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 134 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 133 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 131 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 130 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 129 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 128 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int efx_ef10_ptp_set_ts_sync_events (struct efx_nic*,int,int) ; 
 int efx_ptp_change_mode (struct efx_nic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_ptp_set_ts_config(struct efx_nic *efx,
				      struct hwtstamp_config *init)
{
	int rc;

	switch (init->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		efx_ef10_ptp_set_ts_sync_events(efx, false, false);
		/* if TX timestamping is still requested then leave PTP on */
		return efx_ptp_change_mode(efx,
					   init->tx_type != HWTSTAMP_TX_OFF, 0);
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_NTP_ALL:
		init->rx_filter = HWTSTAMP_FILTER_ALL;
		rc = efx_ptp_change_mode(efx, true, 0);
		if (!rc)
			rc = efx_ef10_ptp_set_ts_sync_events(efx, true, false);
		if (rc)
			efx_ptp_change_mode(efx, false, 0);
		return rc;
	default:
		return -ERANGE;
	}
}