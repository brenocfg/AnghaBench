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
struct efx_ptp_data {scalar_t__ evt_frag_idx; int evt_code; int /*<<< orphan*/ * evt_frags; int /*<<< orphan*/  enabled; } ;
struct efx_nic {int ptp_warned; int /*<<< orphan*/  net_dev; struct efx_ptp_data* ptp_data; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONT ; 
 int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_EVENT_FRAGS ; 
 int /*<<< orphan*/  MCDI_EVENT_CODE ; 
#define  MCDI_EVENT_CODE_PTP_FAULT 130 
#define  MCDI_EVENT_CODE_PTP_PPS 129 
#define  MCDI_EVENT_CODE_PTP_RX 128 
 int /*<<< orphan*/  MCDI_EVENT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptp_event_fault (struct efx_nic*,struct efx_ptp_data*) ; 
 int /*<<< orphan*/  ptp_event_pps (struct efx_nic*,struct efx_ptp_data*) ; 
 int /*<<< orphan*/  ptp_event_rx (struct efx_nic*,struct efx_ptp_data*) ; 

void efx_ptp_event(struct efx_nic *efx, efx_qword_t *ev)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	int code = EFX_QWORD_FIELD(*ev, MCDI_EVENT_CODE);

	if (!ptp) {
		if (!efx->ptp_warned) {
			netif_warn(efx, drv, efx->net_dev,
				   "Received PTP event but PTP not set up\n");
			efx->ptp_warned = true;
		}
		return;
	}

	if (!ptp->enabled)
		return;

	if (ptp->evt_frag_idx == 0) {
		ptp->evt_code = code;
	} else if (ptp->evt_code != code) {
		netif_err(efx, hw, efx->net_dev,
			  "PTP out of sequence event %d\n", code);
		ptp->evt_frag_idx = 0;
	}

	ptp->evt_frags[ptp->evt_frag_idx++] = *ev;
	if (!MCDI_EVENT_FIELD(*ev, CONT)) {
		/* Process resulting event */
		switch (code) {
		case MCDI_EVENT_CODE_PTP_RX:
			ptp_event_rx(efx, ptp);
			break;
		case MCDI_EVENT_CODE_PTP_FAULT:
			ptp_event_fault(efx, ptp);
			break;
		case MCDI_EVENT_CODE_PTP_PPS:
			ptp_event_pps(efx, ptp);
			break;
		default:
			netif_err(efx, hw, efx->net_dev,
				  "PTP unknown event %d\n", code);
			break;
		}
		ptp->evt_frag_idx = 0;
	} else if (MAX_EVENT_FRAGS == ptp->evt_frag_idx) {
		netif_err(efx, hw, efx->net_dev,
			  "PTP too many event fragments\n");
		ptp->evt_frag_idx = 0;
	}
}