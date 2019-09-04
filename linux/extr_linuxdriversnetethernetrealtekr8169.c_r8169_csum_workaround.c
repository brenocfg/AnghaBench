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
struct sk_buff {scalar_t__ ip_summed; struct sk_buff* next; } ;
struct rtl8169_private {TYPE_2__* dev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {int features; struct net_device_stats stats; } ;
struct TYPE_3__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8169_start_xmit (struct sk_buff*,TYPE_2__*) ; 
 scalar_t__ skb_checksum_help (struct sk_buff*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void r8169_csum_workaround(struct rtl8169_private *tp,
				  struct sk_buff *skb)
{
	if (skb_shinfo(skb)->gso_size) {
		netdev_features_t features = tp->dev->features;
		struct sk_buff *segs, *nskb;

		features &= ~(NETIF_F_SG | NETIF_F_IPV6_CSUM | NETIF_F_TSO6);
		segs = skb_gso_segment(skb, features);
		if (IS_ERR(segs) || !segs)
			goto drop;

		do {
			nskb = segs;
			segs = segs->next;
			nskb->next = NULL;
			rtl8169_start_xmit(nskb, tp->dev);
		} while (segs);

		dev_consume_skb_any(skb);
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (skb_checksum_help(skb) < 0)
			goto drop;

		rtl8169_start_xmit(skb, tp->dev);
	} else {
		struct net_device_stats *stats;

drop:
		stats = &tp->dev->stats;
		stats->tx_dropped++;
		dev_kfree_skb_any(skb);
	}
}