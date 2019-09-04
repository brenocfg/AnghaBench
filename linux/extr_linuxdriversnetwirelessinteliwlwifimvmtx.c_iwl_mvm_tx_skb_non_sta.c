#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  cb; scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ sta_id; } ;
struct TYPE_8__ {scalar_t__ sta_id; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  ap_sta_id; TYPE_3__ mcast_sta; TYPE_2__ bcast_sta; } ;
struct TYPE_11__ {scalar_t__ sta_id; } ;
struct TYPE_7__ {scalar_t__ sta_id; } ;
struct iwl_mvm {scalar_t__ aux_queue; int snif_queue; int /*<<< orphan*/  trans; TYPE_5__ snif_sta; TYPE_1__ aux_sta; } ;
struct iwl_device_cmd {int dummy; } ;
struct TYPE_10__ {TYPE_6__* vif; } ;
struct ieee80211_tx_info {scalar_t__ hw_queue; int flags; TYPE_4__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_12__ {scalar_t__ type; scalar_t__ cab_queue; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*,scalar_t__,int) ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 scalar_t__ IWL_MVM_OFFCHANNEL_QUEUE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int iwl_mvm_get_ctrl_vif_queue (struct iwl_mvm*,struct ieee80211_tx_info*,int /*<<< orphan*/ ) ; 
 struct iwl_device_cmd* iwl_mvm_set_tx_params (struct iwl_mvm*,struct sk_buff*,struct ieee80211_tx_info*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_skb_prepare_status (struct sk_buff*,struct iwl_device_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (TYPE_6__*) ; 
 int /*<<< orphan*/  iwl_trans_free_tx_cmd (int /*<<< orphan*/ ,struct iwl_device_cmd*) ; 
 scalar_t__ iwl_trans_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_device_cmd*,int) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_tx_info*,int /*<<< orphan*/ ,int) ; 

int iwl_mvm_tx_skb_non_sta(struct iwl_mvm *mvm, struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *skb_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_info info;
	struct iwl_device_cmd *dev_cmd;
	u8 sta_id;
	int hdrlen = ieee80211_hdrlen(hdr->frame_control);
	int queue;

	/* IWL_MVM_OFFCHANNEL_QUEUE is used for ROC packets that can be used
	 * in 2 different types of vifs, P2P & STATION. P2P uses the offchannel
	 * queue. STATION (HS2.0) uses the auxiliary context of the FW,
	 * and hence needs to be sent on the aux queue
	 */
	if (skb_info->hw_queue == IWL_MVM_OFFCHANNEL_QUEUE &&
	    skb_info->control.vif->type == NL80211_IFTYPE_STATION)
		skb_info->hw_queue = mvm->aux_queue;

	memcpy(&info, skb->cb, sizeof(info));

	if (WARN_ON_ONCE(info.flags & IEEE80211_TX_CTL_AMPDU))
		return -1;

	if (WARN_ON_ONCE(info.flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM &&
			 (!info.control.vif ||
			  info.hw_queue != info.control.vif->cab_queue)))
		return -1;

	queue = info.hw_queue;

	/*
	 * If the interface on which the frame is sent is the P2P_DEVICE
	 * or an AP/GO interface use the broadcast station associated
	 * with it; otherwise if the interface is a managed interface
	 * use the AP station associated with it for multicast traffic
	 * (this is not possible for unicast packets as a TLDS discovery
	 * response are sent without a station entry); otherwise use the
	 * AUX station.
	 */
	sta_id = mvm->aux_sta.sta_id;
	if (info.control.vif) {
		struct iwl_mvm_vif *mvmvif =
			iwl_mvm_vif_from_mac80211(info.control.vif);

		if (info.control.vif->type == NL80211_IFTYPE_P2P_DEVICE ||
		    info.control.vif->type == NL80211_IFTYPE_AP ||
		    info.control.vif->type == NL80211_IFTYPE_ADHOC) {
			if (info.control.vif->type == NL80211_IFTYPE_P2P_DEVICE)
				sta_id = mvmvif->bcast_sta.sta_id;
			else
				sta_id = mvmvif->mcast_sta.sta_id;

			queue = iwl_mvm_get_ctrl_vif_queue(mvm, &info,
							   hdr->frame_control);
			if (queue < 0)
				return -1;
		} else if (info.control.vif->type == NL80211_IFTYPE_STATION &&
			   is_multicast_ether_addr(hdr->addr1)) {
			u8 ap_sta_id = READ_ONCE(mvmvif->ap_sta_id);

			if (ap_sta_id != IWL_MVM_INVALID_STA)
				sta_id = ap_sta_id;
		} else if (info.control.vif->type == NL80211_IFTYPE_MONITOR) {
			queue = mvm->snif_queue;
			sta_id = mvm->snif_sta.sta_id;
		}
	}

	IWL_DEBUG_TX(mvm, "station Id %d, queue=%d\n", sta_id, queue);

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, &info, hdrlen, NULL, sta_id);
	if (!dev_cmd)
		return -1;

	/* From now on, we cannot access info->control */
	iwl_mvm_skb_prepare_status(skb, dev_cmd);

	if (iwl_trans_tx(mvm->trans, skb, dev_cmd, queue)) {
		iwl_trans_free_tx_cmd(mvm->trans, dev_cmd);
		return -1;
	}

	return 0;
}