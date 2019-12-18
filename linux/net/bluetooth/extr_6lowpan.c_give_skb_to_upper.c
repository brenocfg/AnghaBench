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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int netif_rx_ni (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int give_skb_to_upper(struct sk_buff *skb, struct net_device *dev)
{
	struct sk_buff *skb_cp;

	skb_cp = skb_copy(skb, GFP_ATOMIC);
	if (!skb_cp)
		return NET_RX_DROP;

	return netif_rx_ni(skb_cp);
}