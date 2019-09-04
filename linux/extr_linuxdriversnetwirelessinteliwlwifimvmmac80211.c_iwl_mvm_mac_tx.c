#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct iwl_mvm {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__* vif; } ;
struct ieee80211_tx_info {scalar_t__ hw_queue; TYPE_2__ control; } ;
struct ieee80211_tx_control {struct ieee80211_sta* sta; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_MVM_OFFCHANNEL_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_AUX_RUNNING ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_RUNNING ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_is_bufferable_mmpdu (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_defer_tx (struct iwl_mvm*,struct ieee80211_sta*,struct sk_buff*) ; 
 scalar_t__ iwl_mvm_is_radio_killed (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_tx_skb (struct iwl_mvm*,struct sk_buff*,struct ieee80211_sta*) ; 
 scalar_t__ iwl_mvm_tx_skb_non_sta (struct iwl_mvm*,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_tx(struct ieee80211_hw *hw,
			   struct ieee80211_tx_control *control,
			   struct sk_buff *skb)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct ieee80211_sta *sta = control->sta;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (void *)skb->data;

	if (iwl_mvm_is_radio_killed(mvm)) {
		IWL_DEBUG_DROP(mvm, "Dropping - RF/CT KILL\n");
		goto drop;
	}

	if (info->hw_queue == IWL_MVM_OFFCHANNEL_QUEUE &&
	    !test_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status) &&
	    !test_bit(IWL_MVM_STATUS_ROC_AUX_RUNNING, &mvm->status))
		goto drop;

	/* treat non-bufferable MMPDUs on AP interfaces as broadcast */
	if ((info->control.vif->type == NL80211_IFTYPE_AP ||
	     info->control.vif->type == NL80211_IFTYPE_ADHOC) &&
	    ieee80211_is_mgmt(hdr->frame_control) &&
	    !ieee80211_is_bufferable_mmpdu(hdr->frame_control))
		sta = NULL;

	if (sta) {
		if (iwl_mvm_defer_tx(mvm, sta, skb))
			return;
		if (iwl_mvm_tx_skb(mvm, skb, sta))
			goto drop;
		return;
	}

	if (iwl_mvm_tx_skb_non_sta(mvm, skb))
		goto drop;
	return;
 drop:
	ieee80211_free_txskb(hw, skb);
}