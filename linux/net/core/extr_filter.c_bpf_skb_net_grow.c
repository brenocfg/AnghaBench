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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct skb_shared_info {int gso_type; scalar_t__ gso_segs; } ;
struct sk_buff {scalar_t__ protocol; int encapsulation; scalar_t__ network_header; scalar_t__ mac_header; scalar_t__ transport_header; scalar_t__ inner_transport_header; scalar_t__ inner_network_header; scalar_t__ inner_mac_header; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int BPF_ADJ_ROOM_ENCAP_L2_SHIFT ; 
 int BPF_F_ADJ_ROOM_ENCAP_L3_IPV4 ; 
 int BPF_F_ADJ_ROOM_ENCAP_L3_IPV6 ; 
 int BPF_F_ADJ_ROOM_ENCAP_L3_MASK ; 
 int BPF_F_ADJ_ROOM_ENCAP_L4_GRE ; 
 int BPF_F_ADJ_ROOM_ENCAP_L4_UDP ; 
 int BPF_F_ADJ_ROOM_FIXED_GSO ; 
 int EALREADY ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 unsigned int SKB_GSO_DODGY ; 
 unsigned int SKB_GSO_GRE ; 
 unsigned int SKB_GSO_IPXIP4 ; 
 unsigned int SKB_GSO_IPXIP6 ; 
 int SKB_GSO_UDP_L4 ; 
 unsigned int SKB_GSO_UDP_TUNNEL ; 
 int bpf_skb_net_hdr_push (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_decrease_gso_size (struct skb_shared_info*,scalar_t__) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso_tcp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_inner_protocol (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,scalar_t__) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_net_grow(struct sk_buff *skb, u32 off, u32 len_diff,
			    u64 flags)
{
	u8 inner_mac_len = flags >> BPF_ADJ_ROOM_ENCAP_L2_SHIFT;
	bool encap = flags & BPF_F_ADJ_ROOM_ENCAP_L3_MASK;
	u16 mac_len = 0, inner_net = 0, inner_trans = 0;
	unsigned int gso_type = SKB_GSO_DODGY;
	int ret;

	if (skb_is_gso(skb) && !skb_is_gso_tcp(skb)) {
		/* udp gso_size delineates datagrams, only allow if fixed */
		if (!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ||
		    !(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			return -ENOTSUPP;
	}

	ret = skb_cow_head(skb, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (encap) {
		if (skb->protocol != htons(ETH_P_IP) &&
		    skb->protocol != htons(ETH_P_IPV6))
			return -ENOTSUPP;

		if (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4 &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			return -EINVAL;

		if (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP)
			return -EINVAL;

		if (skb->encapsulation)
			return -EALREADY;

		mac_len = skb->network_header - skb->mac_header;
		inner_net = skb->network_header;
		if (inner_mac_len > len_diff)
			return -EINVAL;
		inner_trans = skb->transport_header;
	}

	ret = bpf_skb_net_hdr_push(skb, off, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (encap) {
		skb->inner_mac_header = inner_net - inner_mac_len;
		skb->inner_network_header = inner_net;
		skb->inner_transport_header = inner_trans;
		skb_set_inner_protocol(skb, skb->protocol);

		skb->encapsulation = 1;
		skb_set_network_header(skb, mac_len);

		if (flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP)
			gso_type |= SKB_GSO_UDP_TUNNEL;
		else if (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE)
			gso_type |= SKB_GSO_GRE;
		else if (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			gso_type |= SKB_GSO_IPXIP6;
		else if (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4)
			gso_type |= SKB_GSO_IPXIP4;

		if (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE ||
		    flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP) {
			int nh_len = flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6 ?
					sizeof(struct ipv6hdr) :
					sizeof(struct iphdr);

			skb_set_transport_header(skb, mac_len + nh_len);
		}

		/* Match skb->protocol to new outer l3 protocol */
		if (skb->protocol == htons(ETH_P_IP) &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			skb->protocol = htons(ETH_P_IPV6);
		else if (skb->protocol == htons(ETH_P_IPV6) &&
			 flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4)
			skb->protocol = htons(ETH_P_IP);
	}

	if (skb_is_gso(skb)) {
		struct skb_shared_info *shinfo = skb_shinfo(skb);

		/* Due to header grow, MSS needs to be downgraded. */
		if (!(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			skb_decrease_gso_size(shinfo, len_diff);

		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= gso_type;
		shinfo->gso_segs = 0;
	}

	return 0;
}