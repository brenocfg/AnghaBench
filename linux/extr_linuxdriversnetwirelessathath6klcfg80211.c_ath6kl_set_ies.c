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
struct cfg80211_beacon_data {int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  beacon_ies_len; int /*<<< orphan*/  beacon_ies; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_FRAME_ASSOC_RESP ; 
 int /*<<< orphan*/  WMI_FRAME_BEACON ; 
 int ath6kl_set_ap_probe_resp_ies (struct ath6kl_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_set_appie_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_set_ies(struct ath6kl_vif *vif,
			  struct cfg80211_beacon_data *info)
{
	struct ath6kl *ar = vif->ar;
	int res;

	/* this also clears IE in fw if it's not set */
	res = ath6kl_wmi_set_appie_cmd(ar->wmi, vif->fw_vif_idx,
				       WMI_FRAME_BEACON,
				       info->beacon_ies,
				       info->beacon_ies_len);
	if (res)
		return res;

	/* this also clears IE in fw if it's not set */
	res = ath6kl_set_ap_probe_resp_ies(vif, info->proberesp_ies,
					   info->proberesp_ies_len);
	if (res)
		return res;

	/* this also clears IE in fw if it's not set */
	res = ath6kl_wmi_set_appie_cmd(ar->wmi, vif->fw_vif_idx,
				       WMI_FRAME_ASSOC_RESP,
				       info->assocresp_ies,
				       info->assocresp_ies_len);
	if (res)
		return res;

	return 0;
}