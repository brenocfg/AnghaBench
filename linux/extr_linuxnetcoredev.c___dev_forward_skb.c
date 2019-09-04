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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int ____dev_forward_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __dev_forward_skb(struct net_device *dev, struct sk_buff *skb)
{
	int ret = ____dev_forward_skb(dev, skb);

	if (likely(!ret)) {
		skb->protocol = eth_type_trans(skb, dev);
		skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);
	}

	return ret;
}