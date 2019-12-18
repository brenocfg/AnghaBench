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
struct wiphy {int dummy; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_2__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP ; 
 int /*<<< orphan*/  __ieee80211_subif_start_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

int ieee80211_probe_mesh_link(struct wiphy *wiphy, struct net_device *dev,
			      const u8 *buf, size_t len)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + len +
			    30 + /* header size */
			    18); /* 11s header size */
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	skb_put_data(skb, buf, len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_802_3);
	skb_reset_network_header(skb);
	skb_reset_mac_header(skb);

	local_bh_disable();
	__ieee80211_subif_start_xmit(skb, skb->dev, 0,
				     IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP);
	local_bh_enable();

	return 0;
}