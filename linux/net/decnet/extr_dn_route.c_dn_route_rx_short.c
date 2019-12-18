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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  dev; } ;
struct dn_skb_cb {unsigned char hops; void* src; void* dst; } ;
typedef  void* __le16 ;

/* Variables and functions */
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  NFPROTO_DECNET ; 
 int /*<<< orphan*/  NF_DN_PRE_ROUTING ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_route_rx_packet ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int dn_route_rx_short(struct sk_buff *skb)
{
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	unsigned char *ptr = skb->data;

	if (!pskb_may_pull(skb, 6)) /* 5 for short header + 1 for shortest nsp */
		goto drop_it;

	skb_pull(skb, 5);
	skb_reset_transport_header(skb);

	cb->dst = *(__le16 *)ptr;
	ptr += 2;
	cb->src = *(__le16 *)ptr;
	ptr += 2;
	cb->hops = *ptr & 0x3f;

	return NF_HOOK(NFPROTO_DECNET, NF_DN_PRE_ROUTING,
		       &init_net, NULL, skb, skb->dev, NULL,
		       dn_route_rx_packet);

drop_it:
	kfree_skb(skb);
	return NET_RX_DROP;
}