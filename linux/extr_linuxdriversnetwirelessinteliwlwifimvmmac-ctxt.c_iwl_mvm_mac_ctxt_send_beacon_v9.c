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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct iwl_mvm_vif {scalar_t__ id; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_mac_beacon_cmd {void* ecsa_offset; void* csa_offset; int /*<<< orphan*/  tim_size; int /*<<< orphan*/  tim_idx; void* template_id; void* byte_cnt; void* flags; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_tx_info {int dummy; } ;
typedef  int /*<<< orphan*/  beacon_cmd ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ IWL_FIRST_CCK_RATE ; 
 int /*<<< orphan*/  IWL_MAC_BEACON_CCK ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  WLAN_EID_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  WLAN_EID_EXT_CHANSWITCH_ANN ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_find_ie_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_mac80211_idx_to_hwrate (scalar_t__) ; 
 scalar_t__ iwl_mvm_mac_ctxt_get_lowest_rate (struct ieee80211_tx_info*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_send_beacon_cmd (struct iwl_mvm*,struct sk_buff*,struct iwl_mac_beacon_cmd*,int) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_set_tim (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_send_beacon_v9(struct iwl_mvm *mvm,
					   struct ieee80211_vif *vif,
					   struct sk_buff *beacon)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(beacon);
	struct iwl_mac_beacon_cmd beacon_cmd = {};
	u8 rate = iwl_mvm_mac_ctxt_get_lowest_rate(info, vif);
	u16 flags;

	flags = iwl_mvm_mac80211_idx_to_hwrate(rate);

	if (rate == IWL_FIRST_CCK_RATE)
		flags |= IWL_MAC_BEACON_CCK;

	beacon_cmd.flags = cpu_to_le16(flags);
	beacon_cmd.byte_cnt = cpu_to_le16((u16)beacon->len);
	beacon_cmd.template_id = cpu_to_le32((u32)mvmvif->id);

	if (vif->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->len);

	beacon_cmd.csa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_CHANNEL_SWITCH,
						   beacon->len));
	beacon_cmd.ecsa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_EXT_CHANSWITCH_ANN,
						   beacon->len));

	return iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						sizeof(beacon_cmd));
}