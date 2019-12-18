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
struct tipc_media_addr {int /*<<< orphan*/  value; } ;
struct tipc_bearer {int /*<<< orphan*/  media_ptr; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; scalar_t__ hard_header_len; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TIPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SKB_DATA_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

int tipc_l2_send_msg(struct net *net, struct sk_buff *skb,
		     struct tipc_bearer *b, struct tipc_media_addr *dest)
{
	struct net_device *dev;
	int delta;

	dev = (struct net_device *)rcu_dereference(b->media_ptr);
	if (!dev)
		return 0;

	delta = SKB_DATA_ALIGN(dev->hard_header_len - skb_headroom(skb));
	if ((delta > 0) && pskb_expand_head(skb, delta, 0, GFP_ATOMIC)) {
		kfree_skb(skb);
		return 0;
	}
	skb_reset_network_header(skb);
	skb->dev = dev;
	skb->protocol = htons(ETH_P_TIPC);
	dev_hard_header(skb, dev, ETH_P_TIPC, dest->value,
			dev->dev_addr, skb->len);
	dev_queue_xmit(skb);
	return 0;
}