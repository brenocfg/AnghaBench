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
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  mac_len; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ skb_mac_header_was_set (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_do_netdev_egress(struct sk_buff *skb, struct net_device *dev)
{
	if (skb_mac_header_was_set(skb))
		skb_push(skb, skb->mac_len);

	skb->dev = dev;
	dev_queue_xmit(skb);
}