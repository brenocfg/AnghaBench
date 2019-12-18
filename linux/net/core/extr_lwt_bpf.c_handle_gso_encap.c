#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int /*<<< orphan*/  check; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct gre_base_hdr {int flags; } ;
typedef  int __u8 ;
struct TYPE_6__ {int protocol; } ;
struct TYPE_5__ {int nexthdr; } ;
struct TYPE_4__ {int gso_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int GRE_CSUM ; 
#define  IPPROTO_GRE 131 
#define  IPPROTO_IP 130 
#define  IPPROTO_IPV6 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  SKB_GSO_GRE ; 
 int /*<<< orphan*/  SKB_GSO_GRE_CSUM ; 
 int /*<<< orphan*/  SKB_GSO_IPXIP4 ; 
 int /*<<< orphan*/  SKB_GSO_IPXIP6 ; 
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int /*<<< orphan*/  SKB_GSO_UDP_TUNNEL ; 
 int /*<<< orphan*/  SKB_GSO_UDP_TUNNEL_CSUM ; 
 int handle_gso_type (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 void* skb_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int handle_gso_encap(struct sk_buff *skb, bool ipv4, int encap_len)
{
	int next_hdr_offset;
	void *next_hdr;
	__u8 protocol;

	/* SCTP and UDP_L4 gso need more nuanced handling than what
	 * handle_gso_type() does above: skb_decrease_gso_size() is not enough.
	 * So at the moment only TCP GSO packets are let through.
	 */
	if (!(skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
		return -ENOTSUPP;

	if (ipv4) {
		protocol = ip_hdr(skb)->protocol;
		next_hdr_offset = sizeof(struct iphdr);
		next_hdr = skb_network_header(skb) + next_hdr_offset;
	} else {
		protocol = ipv6_hdr(skb)->nexthdr;
		next_hdr_offset = sizeof(struct ipv6hdr);
		next_hdr = skb_network_header(skb) + next_hdr_offset;
	}

	switch (protocol) {
	case IPPROTO_GRE:
		next_hdr_offset += sizeof(struct gre_base_hdr);
		if (next_hdr_offset > encap_len)
			return -EINVAL;

		if (((struct gre_base_hdr *)next_hdr)->flags & GRE_CSUM)
			return handle_gso_type(skb, SKB_GSO_GRE_CSUM,
					       encap_len);
		return handle_gso_type(skb, SKB_GSO_GRE, encap_len);

	case IPPROTO_UDP:
		next_hdr_offset += sizeof(struct udphdr);
		if (next_hdr_offset > encap_len)
			return -EINVAL;

		if (((struct udphdr *)next_hdr)->check)
			return handle_gso_type(skb, SKB_GSO_UDP_TUNNEL_CSUM,
					       encap_len);
		return handle_gso_type(skb, SKB_GSO_UDP_TUNNEL, encap_len);

	case IPPROTO_IP:
	case IPPROTO_IPV6:
		if (ipv4)
			return handle_gso_type(skb, SKB_GSO_IPXIP4, encap_len);
		else
			return handle_gso_type(skb, SKB_GSO_IPXIP6, encap_len);

	default:
		return -EPROTONOSUPPORT;
	}
}