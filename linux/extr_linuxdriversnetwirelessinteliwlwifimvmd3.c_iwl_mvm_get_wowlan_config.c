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
struct iwl_wowlan_config_cmd {int flags; int /*<<< orphan*/  wakeup_filter; int /*<<< orphan*/  non_qos_seq; int /*<<< orphan*/  is_11n_connection; } ;
struct iwl_mvm_vif {int dummy; } ;
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;
struct cfg80211_wowlan {scalar_t__ any; scalar_t__ tcp; scalar_t__ rfkill_release; scalar_t__ n_patterns; scalar_t__ four_way_handshake; scalar_t__ eap_identity_req; scalar_t__ gtk_rekey_failure; scalar_t__ magic_pkt; scalar_t__ disconnect; } ;

/* Variables and functions */
 int ENABLE_DHCP_FILTERING ; 
 int ENABLE_L3_FILTERING ; 
 int ENABLE_NBNS_FILTERING ; 
 int IWL_WOWLAN_WAKEUP_4WAY_HANDSHAKE ; 
 int IWL_WOWLAN_WAKEUP_BCN_FILTERING ; 
 int IWL_WOWLAN_WAKEUP_BEACON_MISS ; 
 int IWL_WOWLAN_WAKEUP_EAP_IDENT_REQ ; 
 int IWL_WOWLAN_WAKEUP_GTK_REKEY_FAIL ; 
 int IWL_WOWLAN_WAKEUP_LINK_CHANGE ; 
 int IWL_WOWLAN_WAKEUP_MAGIC_PACKET ; 
 int IWL_WOWLAN_WAKEUP_PATTERN_MATCH ; 
 int IWL_WOWLAN_WAKEUP_REMOTE_LINK_LOSS ; 
 int IWL_WOWLAN_WAKEUP_REMOTE_SIGNATURE_TABLE ; 
 int IWL_WOWLAN_WAKEUP_REMOTE_WAKEUP_PACKET ; 
 int IWL_WOWLAN_WAKEUP_RF_KILL_DEASSERT ; 
 int IWL_WOWLAN_WAKEUP_RX_FRAME ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int iwl_mvm_get_last_nonqos_seq (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_set_wowlan_qos_seq (struct iwl_mvm_sta*,struct iwl_wowlan_config_cmd*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

__attribute__((used)) static int
iwl_mvm_get_wowlan_config(struct iwl_mvm *mvm,
			  struct cfg80211_wowlan *wowlan,
			  struct iwl_wowlan_config_cmd *wowlan_config_cmd,
			  struct ieee80211_vif *vif, struct iwl_mvm_vif *mvmvif,
			  struct ieee80211_sta *ap_sta)
{
	int ret;
	struct iwl_mvm_sta *mvm_ap_sta = iwl_mvm_sta_from_mac80211(ap_sta);

	/* TODO: wowlan_config_cmd->wowlan_ba_teardown_tids */

	wowlan_config_cmd->is_11n_connection =
					ap_sta->ht_cap.ht_supported;
	wowlan_config_cmd->flags = ENABLE_L3_FILTERING |
		ENABLE_NBNS_FILTERING | ENABLE_DHCP_FILTERING;

	/* Query the last used seqno and set it */
	ret = iwl_mvm_get_last_nonqos_seq(mvm, vif);
	if (ret < 0)
		return ret;

	wowlan_config_cmd->non_qos_seq = cpu_to_le16(ret);

	iwl_mvm_set_wowlan_qos_seq(mvm_ap_sta, wowlan_config_cmd);

	if (wowlan->disconnect)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_BEACON_MISS |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE);
	if (wowlan->magic_pkt)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_MAGIC_PACKET);
	if (wowlan->gtk_rekey_failure)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_GTK_REKEY_FAIL);
	if (wowlan->eap_identity_req)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_EAP_IDENT_REQ);
	if (wowlan->four_way_handshake)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_4WAY_HANDSHAKE);
	if (wowlan->n_patterns)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_PATTERN_MATCH);

	if (wowlan->rfkill_release)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_RF_KILL_DEASSERT);

	if (wowlan->tcp) {
		/*
		 * Set the "link change" (really "link lost") flag as well
		 * since that implies losing the TCP connection.
		 */
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_REMOTE_LINK_LOSS |
				    IWL_WOWLAN_WAKEUP_REMOTE_SIGNATURE_TABLE |
				    IWL_WOWLAN_WAKEUP_REMOTE_WAKEUP_PACKET |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE);
	}

	if (wowlan->any) {
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_BEACON_MISS |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE |
				    IWL_WOWLAN_WAKEUP_RX_FRAME |
				    IWL_WOWLAN_WAKEUP_BCN_FILTERING);
	}

	return 0;
}