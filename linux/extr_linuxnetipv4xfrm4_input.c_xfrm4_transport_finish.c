#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_offload {int flags; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  len; scalar_t__ data; } ;
struct iphdr {int protocol; int /*<<< orphan*/  tot_len; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_PRE_ROUTING ; 
 int XFRM_GRO ; 
 TYPE_1__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  skb_mac_header_rebuild (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm4_rcv_encap_finish ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

int xfrm4_transport_finish(struct sk_buff *skb, int async)
{
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct iphdr *iph = ip_hdr(skb);

	iph->protocol = XFRM_MODE_SKB_CB(skb)->protocol;

#ifndef CONFIG_NETFILTER
	if (!async)
		return -iph->protocol;
#endif

	__skb_push(skb, skb->data - skb_network_header(skb));
	iph->tot_len = htons(skb->len);
	ip_send_check(iph);

	if (xo && (xo->flags & XFRM_GRO)) {
		skb_mac_header_rebuild(skb);
		skb_reset_transport_header(skb);
		return 0;
	}

	NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING,
		dev_net(skb->dev), NULL, skb, skb->dev, NULL,
		xfrm4_rcv_encap_finish);
	return 0;
}