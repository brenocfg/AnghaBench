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
struct ath6kl_vif {int sme_state; int /*<<< orphan*/  fw_vif_idx; TYPE_1__* ar; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 scalar_t__ ATH6KL_STATE_RECOVERY ; 
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  CONNECT_PEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SME_CONNECTED 130 
#define  SME_CONNECTING 129 
#define  SME_DISCONNECTED 128 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  ath6kl_cfg80211_scan_complete_event (struct ath6kl_vif*,int) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_sscan_disable (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 int /*<<< orphan*/  ath6kl_wmi_disconnect_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ath6kl_wmi_scanparams_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_cfg80211_stop(struct ath6kl_vif *vif)
{
	ath6kl_cfg80211_sscan_disable(vif);

	switch (vif->sme_state) {
	case SME_DISCONNECTED:
		break;
	case SME_CONNECTING:
		cfg80211_connect_result(vif->ndev, vif->bssid, NULL, 0,
					NULL, 0,
					WLAN_STATUS_UNSPECIFIED_FAILURE,
					GFP_KERNEL);
		break;
	case SME_CONNECTED:
		cfg80211_disconnected(vif->ndev, 0, NULL, 0, true, GFP_KERNEL);
		break;
	}

	if (vif->ar->state != ATH6KL_STATE_RECOVERY &&
	    (test_bit(CONNECTED, &vif->flags) ||
	    test_bit(CONNECT_PEND, &vif->flags)))
		ath6kl_wmi_disconnect_cmd(vif->ar->wmi, vif->fw_vif_idx);

	vif->sme_state = SME_DISCONNECTED;
	clear_bit(CONNECTED, &vif->flags);
	clear_bit(CONNECT_PEND, &vif->flags);

	/* Stop netdev queues, needed during recovery */
	netif_stop_queue(vif->ndev);
	netif_carrier_off(vif->ndev);

	/* disable scanning */
	if (vif->ar->state != ATH6KL_STATE_RECOVERY &&
	    ath6kl_wmi_scanparams_cmd(vif->ar->wmi, vif->fw_vif_idx, 0xFFFF,
				      0, 0, 0, 0, 0, 0, 0, 0, 0) != 0)
		ath6kl_warn("failed to disable scan during stop\n");

	ath6kl_cfg80211_scan_complete_event(vif, true);
}