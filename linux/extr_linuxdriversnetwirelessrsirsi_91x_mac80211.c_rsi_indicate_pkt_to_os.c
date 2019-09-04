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
struct sk_buff {int dummy; } ;
struct rsi_hw {int /*<<< orphan*/  sc_nvifs; struct ieee80211_hw* hw; } ;
struct rsi_common {scalar_t__ iface_down; struct rsi_hw* priv; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  rsi_fill_rx_status (struct ieee80211_hw*,struct sk_buff*,struct rsi_common*,struct ieee80211_rx_status*) ; 

void rsi_indicate_pkt_to_os(struct rsi_common *common,
			    struct sk_buff *skb)
{
	struct rsi_hw *adapter = common->priv;
	struct ieee80211_hw *hw = adapter->hw;
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);

	if ((common->iface_down) || (!adapter->sc_nvifs)) {
		dev_kfree_skb(skb);
		return;
	}

	/* filling in the ieee80211_rx_status flags */
	rsi_fill_rx_status(hw, skb, common, rx_status);

	ieee80211_rx_irqsafe(hw, skb);
}