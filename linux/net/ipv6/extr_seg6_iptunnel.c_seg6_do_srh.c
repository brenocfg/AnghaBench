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
struct sk_buff {void* protocol; scalar_t__ len; int /*<<< orphan*/  mac_len; } ;
struct seg6_iptunnel_encap {int mode; int /*<<< orphan*/  srh; } ;
struct ipv6hdr {int dummy; } ;
struct dst_entry {int /*<<< orphan*/  lwtstate; } ;
struct TYPE_2__ {void* payload_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPPROTO_IPIP ; 
 int IPPROTO_IPV6 ; 
 int NEXTHDR_NONE ; 
#define  SEG6_IPTUN_MODE_ENCAP 130 
#define  SEG6_IPTUN_MODE_INLINE 129 
#define  SEG6_IPTUN_MODE_L2ENCAP 128 
 int /*<<< orphan*/  SKB_GSO_IPXIP6 ; 
 void* htons (scalar_t__) ; 
 int iptunnel_handle_offloads (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int seg6_do_srh_encap (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int seg6_do_srh_inline (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct seg6_iptunnel_encap* seg6_encap_lwtunnel (int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_rebuild (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_inner_protocol (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  skb_set_inner_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int seg6_do_srh(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct seg6_iptunnel_encap *tinfo;
	int proto, err = 0;

	tinfo = seg6_encap_lwtunnel(dst->lwtstate);

	switch (tinfo->mode) {
	case SEG6_IPTUN_MODE_INLINE:
		if (skb->protocol != htons(ETH_P_IPV6))
			return -EINVAL;

		err = seg6_do_srh_inline(skb, tinfo->srh);
		if (err)
			return err;
		break;
	case SEG6_IPTUN_MODE_ENCAP:
		err = iptunnel_handle_offloads(skb, SKB_GSO_IPXIP6);
		if (err)
			return err;

		if (skb->protocol == htons(ETH_P_IPV6))
			proto = IPPROTO_IPV6;
		else if (skb->protocol == htons(ETH_P_IP))
			proto = IPPROTO_IPIP;
		else
			return -EINVAL;

		err = seg6_do_srh_encap(skb, tinfo->srh, proto);
		if (err)
			return err;

		skb_set_inner_transport_header(skb, skb_transport_offset(skb));
		skb_set_inner_protocol(skb, skb->protocol);
		skb->protocol = htons(ETH_P_IPV6);
		break;
	case SEG6_IPTUN_MODE_L2ENCAP:
		if (!skb_mac_header_was_set(skb))
			return -EINVAL;

		if (pskb_expand_head(skb, skb->mac_len, 0, GFP_ATOMIC) < 0)
			return -ENOMEM;

		skb_mac_header_rebuild(skb);
		skb_push(skb, skb->mac_len);

		err = seg6_do_srh_encap(skb, tinfo->srh, NEXTHDR_NONE);
		if (err)
			return err;

		skb->protocol = htons(ETH_P_IPV6);
		break;
	}

	ipv6_hdr(skb)->payload_len = htons(skb->len - sizeof(struct ipv6hdr));
	skb_set_transport_header(skb, sizeof(struct ipv6hdr));

	return 0;
}