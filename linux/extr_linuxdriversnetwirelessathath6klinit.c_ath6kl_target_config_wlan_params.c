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
struct ath6kl {int conf_flags; int p2p; int vif_max; int /*<<< orphan*/  wmi; int /*<<< orphan*/  rx_meta_ver; } ;

/* Variables and functions */
 int ATH6KL_CONF_ENABLE_TX_BURST ; 
 int ATH6KL_CONF_IGNORE_ERP_BARKER ; 
 int ATH6KL_CONF_IGNORE_PS_FAIL_EVT_IN_SCAN ; 
 int /*<<< orphan*/  ATH6KL_DBG_TRC ; 
 int /*<<< orphan*/  IGNORE_PS_FAIL_DURING_SCAN ; 
 int P2P_FLAG_CAPABILITIES_REQ ; 
 int P2P_FLAG_HMODEL_REQ ; 
 int P2P_FLAG_MACADDR_REQ ; 
 int /*<<< orphan*/  WLAN_CONFIG_DISCONNECT_TIMEOUT ; 
 int /*<<< orphan*/  WLAN_CONFIG_KEEP_ALIVE_INTERVAL ; 
 int /*<<< orphan*/  WMI_FOLLOW_BARKER_IN_ERP ; 
 int /*<<< orphan*/  WMI_TXOP_DISABLED ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_wmi_disctimeout_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_info_req_cmd (int /*<<< orphan*/ ,int,int) ; 
 int ath6kl_wmi_pmparams_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_probe_report_req_cmd (int /*<<< orphan*/ ,int,int) ; 
 int ath6kl_wmi_set_keepalive_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_lpreamble_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_rx_frame_format_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_wmm_txop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_target_config_wlan_params(struct ath6kl *ar, int idx)
{
	int ret;

	/*
	 * Configure the device for rx dot11 header rules. "0,0" are the
	 * default values. Required if checksum offload is needed. Set
	 * RxMetaVersion to 2.
	 */
	ret = ath6kl_wmi_set_rx_frame_format_cmd(ar->wmi, idx,
						 ar->rx_meta_ver, 0, 0);
	if (ret) {
		ath6kl_err("unable to set the rx frame format: %d\n", ret);
		return ret;
	}

	if (ar->conf_flags & ATH6KL_CONF_IGNORE_PS_FAIL_EVT_IN_SCAN) {
		ret = ath6kl_wmi_pmparams_cmd(ar->wmi, idx, 0, 1, 0, 0, 1,
					      IGNORE_PS_FAIL_DURING_SCAN);
		if (ret) {
			ath6kl_err("unable to set power save fail event policy: %d\n",
				   ret);
			return ret;
		}
	}

	if (!(ar->conf_flags & ATH6KL_CONF_IGNORE_ERP_BARKER)) {
		ret = ath6kl_wmi_set_lpreamble_cmd(ar->wmi, idx, 0,
						   WMI_FOLLOW_BARKER_IN_ERP);
		if (ret) {
			ath6kl_err("unable to set barker preamble policy: %d\n",
				   ret);
			return ret;
		}
	}

	ret = ath6kl_wmi_set_keepalive_cmd(ar->wmi, idx,
					   WLAN_CONFIG_KEEP_ALIVE_INTERVAL);
	if (ret) {
		ath6kl_err("unable to set keep alive interval: %d\n", ret);
		return ret;
	}

	ret = ath6kl_wmi_disctimeout_cmd(ar->wmi, idx,
					 WLAN_CONFIG_DISCONNECT_TIMEOUT);
	if (ret) {
		ath6kl_err("unable to set disconnect timeout: %d\n", ret);
		return ret;
	}

	if (!(ar->conf_flags & ATH6KL_CONF_ENABLE_TX_BURST)) {
		ret = ath6kl_wmi_set_wmm_txop(ar->wmi, idx, WMI_TXOP_DISABLED);
		if (ret) {
			ath6kl_err("unable to set txop bursting: %d\n", ret);
			return ret;
		}
	}

	if (ar->p2p && (ar->vif_max == 1 || idx)) {
		ret = ath6kl_wmi_info_req_cmd(ar->wmi, idx,
					      P2P_FLAG_CAPABILITIES_REQ |
					      P2P_FLAG_MACADDR_REQ |
					      P2P_FLAG_HMODEL_REQ);
		if (ret) {
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "failed to request P2P capabilities (%d) - assuming P2P not supported\n",
				   ret);
			ar->p2p = false;
		}
	}

	if (ar->p2p && (ar->vif_max == 1 || idx)) {
		/* Enable Probe Request reporting for P2P */
		ret = ath6kl_wmi_probe_report_req_cmd(ar->wmi, idx, true);
		if (ret) {
			ath6kl_dbg(ATH6KL_DBG_TRC,
				   "failed to enable Probe Request reporting (%d)\n",
				   ret);
		}
	}

	return ret;
}