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
struct ieee802154_local {int /*<<< orphan*/  skb_queue; } ;

/* Variables and functions */
#define  IEEE802154_RX_MSG 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  ieee802154_rx (struct ieee802154_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee802154_tasklet_handler(unsigned long data)
{
	struct ieee802154_local *local = (struct ieee802154_local *)data;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&local->skb_queue))) {
		switch (skb->pkt_type) {
		case IEEE802154_RX_MSG:
			/* Clear skb->pkt_type in order to not confuse kernel
			 * netstack.
			 */
			skb->pkt_type = 0;
			ieee802154_rx(local, skb);
			break;
		default:
			WARN(1, "mac802154: Packet is of unknown type %d\n",
			     skb->pkt_type);
			kfree_skb(skb);
			break;
		}
	}
}