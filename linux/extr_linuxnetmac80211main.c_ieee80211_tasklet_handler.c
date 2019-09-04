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
struct sk_buff {int pkt_type; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; int /*<<< orphan*/  skb_queue_unreliable; int /*<<< orphan*/  skb_queue; } ;

/* Variables and functions */
#define  IEEE80211_RX_MSG 129 
#define  IEEE80211_TX_STATUS_MSG 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_tasklet_handler(unsigned long data)
{
	struct ieee80211_local *local = (struct ieee80211_local *) data;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&local->skb_queue)) ||
	       (skb = skb_dequeue(&local->skb_queue_unreliable))) {
		switch (skb->pkt_type) {
		case IEEE80211_RX_MSG:
			/* Clear skb->pkt_type in order to not confuse kernel
			 * netstack. */
			skb->pkt_type = 0;
			ieee80211_rx(&local->hw, skb);
			break;
		case IEEE80211_TX_STATUS_MSG:
			skb->pkt_type = 0;
			ieee80211_tx_status(&local->hw, skb);
			break;
		default:
			WARN(1, "mac80211: Packet is of unknown type %d\n",
			     skb->pkt_type);
			dev_kfree_skb(skb);
			break;
		}
	}
}