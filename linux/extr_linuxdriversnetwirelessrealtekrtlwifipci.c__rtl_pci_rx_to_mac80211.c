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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  rx_status ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  rtl_action_proc (struct ieee80211_hw*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void _rtl_pci_rx_to_mac80211(struct ieee80211_hw *hw,
				    struct sk_buff *skb,
				    struct ieee80211_rx_status rx_status)
{
	if (unlikely(!rtl_action_proc(hw, skb, false))) {
		dev_kfree_skb_any(skb);
	} else {
		struct sk_buff *uskb = NULL;

		uskb = dev_alloc_skb(skb->len + 128);
		if (likely(uskb)) {
			memcpy(IEEE80211_SKB_RXCB(uskb), &rx_status,
			       sizeof(rx_status));
			skb_put_data(uskb, skb->data, skb->len);
			dev_kfree_skb_any(skb);
			ieee80211_rx_irqsafe(hw, uskb);
		} else {
			ieee80211_rx_irqsafe(hw, skb);
		}
	}
}