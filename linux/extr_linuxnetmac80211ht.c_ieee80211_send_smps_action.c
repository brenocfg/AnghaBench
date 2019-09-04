#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {TYPE_2__* dev; struct ieee80211_local* local; } ;
struct TYPE_10__ {int /*<<< orphan*/  smps_control; int /*<<< orphan*/  action; } ;
struct TYPE_11__ {TYPE_3__ ht_smps; } ;
struct TYPE_12__ {TYPE_4__ u; int /*<<< orphan*/  category; } ;
struct TYPE_13__ {TYPE_5__ action; } ;
struct ieee80211_mgmt {TYPE_6__ u; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct TYPE_8__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  const* dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 TYPE_7__* IEEE80211_SKB_CB (struct sk_buff*) ; 
#define  IEEE80211_SMPS_AUTOMATIC 132 
#define  IEEE80211_SMPS_DYNAMIC 131 
#define  IEEE80211_SMPS_NUM_MODES 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_CATEGORY_HT ; 
 int /*<<< orphan*/  WLAN_HT_ACTION_SMPS ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_DISABLED ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_DYNAMIC ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_STATIC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ieee80211_mgmt* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

int ieee80211_send_smps_action(struct ieee80211_sub_if_data *sdata,
			       enum ieee80211_smps_mode smps, const u8 *da,
			       const u8 *bssid)
{
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_mgmt *action_frame;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(27 + local->hw.extra_tx_headroom);
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	action_frame = skb_put(skb, 27);
	memcpy(action_frame->da, da, ETH_ALEN);
	memcpy(action_frame->sa, sdata->dev->dev_addr, ETH_ALEN);
	memcpy(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_HT;
	action_frame->u.action.u.ht_smps.action = WLAN_HT_ACTION_SMPS;
	switch (smps) {
	case IEEE80211_SMPS_AUTOMATIC:
	case IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		/* fall through */
	case IEEE80211_SMPS_OFF:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DISABLED;
		break;
	case IEEE80211_SMPS_STATIC:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_STATIC;
		break;
	case IEEE80211_SMPS_DYNAMIC:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DYNAMIC;
		break;
	}

	/* we'll do more on status of this frame */
	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
	ieee80211_tx_skb(sdata, skb);

	return 0;
}