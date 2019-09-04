#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ bf_enabled; } ;
struct iwl_mvm_vif {TYPE_3__ bf_data; } ;
struct iwl_mvm {TYPE_2__* fw; struct iwl_mvm_vif* bf_allowed_vif; } ;
struct iwl_mac_power_cmd {int dummy; } ;
struct iwl_beacon_filter_cmd {int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; scalar_t__ p2p; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_BF_CMD_CONFIG_D0I3 ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_BEACON_STORING ; 
 int /*<<< orphan*/  MAC_PM_POWER_TABLE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int _iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int) ; 
 int _iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_beacon_filter_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_power_build_cmd (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mac_power_cmd*,int) ; 
 int /*<<< orphan*/  iwl_mvm_power_log (struct iwl_mvm*,struct iwl_mac_power_cmd*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mac_power_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

int iwl_mvm_update_d0i3_power_mode(struct iwl_mvm *mvm,
				   struct ieee80211_vif *vif,
				   bool enable, u32 flags)
{
	int ret;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mac_power_cmd cmd = {};

	if (vif->type != NL80211_IFTYPE_STATION || vif->p2p)
		return 0;

	if (!vif->bss_conf.assoc)
		return 0;

	iwl_mvm_power_build_cmd(mvm, vif, &cmd, !enable);

	iwl_mvm_power_log(mvm, &cmd);
#ifdef CONFIG_IWLWIFI_DEBUGFS
	memcpy(&mvmvif->mac_pwr_cmd, &cmd, sizeof(cmd));
#endif
	ret = iwl_mvm_send_cmd_pdu(mvm, MAC_PM_POWER_TABLE, flags,
				   sizeof(cmd), &cmd);
	if (ret)
		return ret;

	/* configure beacon filtering */
	if (mvmvif != mvm->bf_allowed_vif)
		return 0;

	if (enable) {
		struct iwl_beacon_filter_cmd cmd_bf = {
			IWL_BF_CMD_CONFIG_D0I3,
			.bf_enable_beacon_filter = cpu_to_le32(1),
		};
		/*
		 * When beacon storing is supported - disable beacon filtering
		 * altogether - the latest beacon will be sent when exiting d0i3
		 */
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_BEACON_STORING))
			ret = _iwl_mvm_disable_beacon_filter(mvm, vif, flags,
							     true);
		else
			ret = _iwl_mvm_enable_beacon_filter(mvm, vif, &cmd_bf,
							    flags, true);
	} else {
		if (mvmvif->bf_data.bf_enabled)
			ret = iwl_mvm_enable_beacon_filter(mvm, vif, flags);
		else
			ret = iwl_mvm_disable_beacon_filter(mvm, vif, flags);
	}

	return ret;
}