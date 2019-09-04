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
typedef  int u32 ;
struct skb_shared_info {int gso_type; scalar_t__ gso_segs; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int SKB_GSO_DODGY ; 
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int bpf_skb_net_hdr_push (struct sk_buff*,int,int const) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clear_hash (struct sk_buff*) ; 
 int skb_cow (struct sk_buff*,int const) ; 
 int /*<<< orphan*/  skb_decrease_gso_size (struct skb_shared_info*,int const) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso_tcp (struct sk_buff*) ; 
 int skb_mac_header_len (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_proto_4_to_6(struct sk_buff *skb)
{
	const u32 len_diff = sizeof(struct ipv6hdr) - sizeof(struct iphdr);
	u32 off = skb_mac_header_len(skb);
	int ret;

	if (skb_is_gso(skb) && !skb_is_gso_tcp(skb))
		return -ENOTSUPP;

	ret = skb_cow(skb, len_diff);
	if (unlikely(ret < 0))
		return ret;

	ret = bpf_skb_net_hdr_push(skb, off, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (skb_is_gso(skb)) {
		struct skb_shared_info *shinfo = skb_shinfo(skb);

		/* SKB_GSO_TCPV4 needs to be changed into
		 * SKB_GSO_TCPV6.
		 */
		if (shinfo->gso_type & SKB_GSO_TCPV4) {
			shinfo->gso_type &= ~SKB_GSO_TCPV4;
			shinfo->gso_type |=  SKB_GSO_TCPV6;
		}

		/* Due to IPv6 header, MSS needs to be downgraded. */
		skb_decrease_gso_size(shinfo, len_diff);
		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	}

	skb->protocol = htons(ETH_P_IPV6);
	skb_clear_hash(skb);

	return 0;
}