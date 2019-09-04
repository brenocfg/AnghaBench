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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_IEEE802154 ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int netif_receive_skb (struct sk_buff*) ; 

__attribute__((used)) static int ieee802154_deliver_skb(struct sk_buff *skb)
{
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->protocol = htons(ETH_P_IEEE802154);

	return netif_receive_skb(skb);
}