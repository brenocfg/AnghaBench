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
struct wiphy {int features; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tdls_data {int action_code; } ;
struct ieee80211_sub_if_data {TYPE_2__* local; } ;
struct TYPE_3__ {struct wiphy* wiphy; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int NL80211_FEATURE_TDLS_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  WLAN_TDLS_CHANNEL_SWITCH_REQUEST 129 
#define  WLAN_TDLS_CHANNEL_SWITCH_RESPONSE 128 
 int /*<<< orphan*/  ieee80211_process_tdls_channel_switch_req (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_process_tdls_channel_switch_resp (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 

__attribute__((used)) static void
ieee80211_process_tdls_channel_switch(struct ieee80211_sub_if_data *sdata,
				      struct sk_buff *skb)
{
	struct ieee80211_tdls_data *tf = (void *)skb->data;
	struct wiphy *wiphy = sdata->local->hw.wiphy;

	ASSERT_RTNL();

	/* make sure the driver supports it */
	if (!(wiphy->features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		return;

	/* we want to access the entire packet */
	if (skb_linearize(skb))
		return;
	/*
	 * The packet/size was already validated by mac80211 Rx path, only look
	 * at the action type.
	 */
	switch (tf->action_code) {
	case WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
		ieee80211_process_tdls_channel_switch_req(sdata, skb);
		break;
	case WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		ieee80211_process_tdls_channel_switch_resp(sdata, skb);
		break;
	default:
		WARN_ON_ONCE(1);
		return;
	}
}