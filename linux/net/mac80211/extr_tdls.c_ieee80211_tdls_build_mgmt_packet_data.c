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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct ieee80211_tdls_lnkie {int dummy; } ;
struct ieee80211_tdls_data {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; struct ieee80211_local* local; } ;
struct ieee80211_mgmt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 135 
#define  WLAN_TDLS_CHANNEL_SWITCH_REQUEST 134 
#define  WLAN_TDLS_CHANNEL_SWITCH_RESPONSE 133 
#define  WLAN_TDLS_DISCOVERY_REQUEST 132 
#define  WLAN_TDLS_SETUP_CONFIRM 131 
#define  WLAN_TDLS_SETUP_REQUEST 130 
#define  WLAN_TDLS_SETUP_RESPONSE 129 
#define  WLAN_TDLS_TEARDOWN 128 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int ieee80211_prep_tdls_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ieee80211_prep_tdls_encap_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_ies (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 
 scalar_t__ max (int,int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *
ieee80211_tdls_build_mgmt_packet_data(struct ieee80211_sub_if_data *sdata,
				      const u8 *peer, u8 action_code,
				      u8 dialog_token, u16 status_code,
				      bool initiator, const u8 *extra_ies,
				      size_t extra_ies_len, u8 oper_class,
				      struct cfg80211_chan_def *chandef)
{
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	int ret;

	skb = netdev_alloc_skb(sdata->dev,
			       local->hw.extra_tx_headroom +
			       max(sizeof(struct ieee80211_mgmt),
				   sizeof(struct ieee80211_tdls_data)) +
			       50 + /* supported rates */
			       10 + /* ext capab */
			       26 + /* max(WMM-info, WMM-param) */
			       2 + max(sizeof(struct ieee80211_ht_cap),
				       sizeof(struct ieee80211_ht_operation)) +
			       2 + max(sizeof(struct ieee80211_vht_cap),
				       sizeof(struct ieee80211_vht_operation)) +
			       50 + /* supported channels */
			       3 + /* 40/20 BSS coex */
			       4 + /* AID */
			       4 + /* oper classes */
			       extra_ies_len +
			       sizeof(struct ieee80211_tdls_lnkie));
	if (!skb)
		return NULL;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_RESPONSE:
	case WLAN_TDLS_SETUP_CONFIRM:
	case WLAN_TDLS_TEARDOWN:
	case WLAN_TDLS_DISCOVERY_REQUEST:
	case WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
	case WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		ret = ieee80211_prep_tdls_encap_data(local->hw.wiphy,
						     sdata->dev, peer,
						     action_code, dialog_token,
						     status_code, skb);
		break;
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		ret = ieee80211_prep_tdls_direct(local->hw.wiphy, sdata->dev,
						 peer, action_code,
						 dialog_token, status_code,
						 skb);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (ret < 0)
		goto fail;

	ieee80211_tdls_add_ies(sdata, skb, peer, action_code, status_code,
			       initiator, extra_ies, extra_ies_len, oper_class,
			       chandef);
	return skb;

fail:
	dev_kfree_skb(skb);
	return NULL;
}