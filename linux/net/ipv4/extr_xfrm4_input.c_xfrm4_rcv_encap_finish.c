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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_route_input_noref (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm4_rcv_encap_finish2 ; 
 scalar_t__ xfrm_trans_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xfrm4_rcv_encap_finish(struct net *net, struct sock *sk,
					 struct sk_buff *skb)
{
	if (!skb_dst(skb)) {
		const struct iphdr *iph = ip_hdr(skb);

		if (ip_route_input_noref(skb, iph->daddr, iph->saddr,
					 iph->tos, skb->dev))
			goto drop;
	}

	if (xfrm_trans_queue(skb, xfrm4_rcv_encap_finish2))
		goto drop;

	return 0;
drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}