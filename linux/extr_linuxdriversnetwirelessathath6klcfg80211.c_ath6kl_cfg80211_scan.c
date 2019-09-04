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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct cfg80211_scan_request {scalar_t__ n_channels; int /*<<< orphan*/  rates; int /*<<< orphan*/  no_cck; TYPE_1__** channels; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  n_ssids; int /*<<< orphan*/  ssids; int /*<<< orphan*/  wdev; } ;
struct ath6kl_vif {struct cfg80211_scan_request* scan_req; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/  usr_bss_filter; } ;
typedef  size_t s8 ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_BSS_FILTER ; 
 int /*<<< orphan*/  ATH6KL_FG_SCAN_INTERVAL ; 
 int /*<<< orphan*/  CLEAR_BSSFILTER_ON_BEACON ; 
 int /*<<< orphan*/  CONNECTED ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WMI_FRAME_PROBE_REQ ; 
 int /*<<< orphan*/  WMI_LONG_SCAN ; 
 scalar_t__ WMI_MAX_CHANNELS ; 
 int /*<<< orphan*/  ath6kl_cfg80211_ready (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_sscan_disable (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_err (char*,...) ; 
 struct ath6kl* ath6kl_priv (int /*<<< orphan*/ ) ; 
 int ath6kl_set_probed_ssids (struct ath6kl*,struct ath6kl_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* ath6kl_vif_from_wdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 int ath6kl_wmi_beginscan_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_bssfilter_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_appie_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_cfg80211_scan(struct wiphy *wiphy,
				struct cfg80211_scan_request *request)
{
	struct ath6kl_vif *vif = ath6kl_vif_from_wdev(request->wdev);
	struct ath6kl *ar = ath6kl_priv(vif->ndev);
	s8 n_channels = 0;
	u16 *channels = NULL;
	int ret = 0;
	u32 force_fg_scan = 0;

	if (!ath6kl_cfg80211_ready(vif))
		return -EIO;

	ath6kl_cfg80211_sscan_disable(vif);

	if (!ar->usr_bss_filter) {
		clear_bit(CLEAR_BSSFILTER_ON_BEACON, &vif->flags);
		ret = ath6kl_wmi_bssfilter_cmd(ar->wmi, vif->fw_vif_idx,
					       ALL_BSS_FILTER, 0);
		if (ret) {
			ath6kl_err("couldn't set bss filtering\n");
			return ret;
		}
	}

	ret = ath6kl_set_probed_ssids(ar, vif, request->ssids,
				      request->n_ssids, NULL, 0);
	if (ret < 0)
		return ret;

	/* this also clears IE in fw if it's not set */
	ret = ath6kl_wmi_set_appie_cmd(ar->wmi, vif->fw_vif_idx,
				       WMI_FRAME_PROBE_REQ,
				       request->ie, request->ie_len);
	if (ret) {
		ath6kl_err("failed to set Probe Request appie for scan\n");
		return ret;
	}

	/*
	 * Scan only the requested channels if the request specifies a set of
	 * channels. If the list is longer than the target supports, do not
	 * configure the list and instead, scan all available channels.
	 */
	if (request->n_channels > 0 &&
	    request->n_channels <= WMI_MAX_CHANNELS) {
		u8 i;

		n_channels = request->n_channels;

		channels = kcalloc(n_channels, sizeof(u16), GFP_KERNEL);
		if (channels == NULL) {
			ath6kl_warn("failed to set scan channels, scan all channels");
			n_channels = 0;
		}

		for (i = 0; i < n_channels; i++)
			channels[i] = request->channels[i]->center_freq;
	}

	if (test_bit(CONNECTED, &vif->flags))
		force_fg_scan = 1;

	vif->scan_req = request;

	ret = ath6kl_wmi_beginscan_cmd(ar->wmi, vif->fw_vif_idx,
				       WMI_LONG_SCAN, force_fg_scan,
				       false, 0,
				       ATH6KL_FG_SCAN_INTERVAL,
				       n_channels, channels,
				       request->no_cck,
				       request->rates);
	if (ret) {
		ath6kl_err("failed to start scan: %d\n", ret);
		vif->scan_req = NULL;
	}

	kfree(channels);

	return ret;
}