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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ protocol; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_get_protocol (struct sk_buff*,scalar_t__,int*) ; 
 int /*<<< orphan*/  br_drop_fake_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_skb_forwardable (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 

int br_dev_queue_push_xmit(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	skb_push(skb, ETH_HLEN);
	if (!is_skb_forwardable(skb->dev, skb))
		goto drop;

	br_drop_fake_rtable(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (skb->protocol == htons(ETH_P_8021Q) ||
	     skb->protocol == htons(ETH_P_8021AD))) {
		int depth;

		if (!__vlan_get_protocol(skb, skb->protocol, &depth))
			goto drop;

		skb_set_network_header(skb, depth);
	}

	dev_queue_xmit(skb);

	return 0;

drop:
	kfree_skb(skb);
	return 0;
}