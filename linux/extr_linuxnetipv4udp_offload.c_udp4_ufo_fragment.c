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
struct udphdr {scalar_t__ check; } ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  encap_hdr_csum; int /*<<< orphan*/  ip_summed; scalar_t__ encapsulation; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_2__ {int gso_type; unsigned int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_F_HW_CSUM ; 
 int SKB_GSO_UDP ; 
 int SKB_GSO_UDP_L4 ; 
 int SKB_GSO_UDP_TUNNEL ; 
 int SKB_GSO_UDP_TUNNEL_CSUM ; 
 struct sk_buff* __udp_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* skb_udp_tunnel_segment (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 scalar_t__ udp_v4_check (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *udp4_ufo_fragment(struct sk_buff *skb,
					 netdev_features_t features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	unsigned int mss;
	__wsum csum;
	struct udphdr *uh;
	struct iphdr *iph;

	if (skb->encapsulation &&
	    (skb_shinfo(skb)->gso_type &
	     (SKB_GSO_UDP_TUNNEL|SKB_GSO_UDP_TUNNEL_CSUM))) {
		segs = skb_udp_tunnel_segment(skb, features, false);
		goto out;
	}

	if (!(skb_shinfo(skb)->gso_type & (SKB_GSO_UDP | SKB_GSO_UDP_L4)))
		goto out;

	if (!pskb_may_pull(skb, sizeof(struct udphdr)))
		goto out;

	if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		return __udp_gso_segment(skb, features);

	mss = skb_shinfo(skb)->gso_size;
	if (unlikely(skb->len <= mss))
		goto out;

	/* Do software UFO. Complete and fill in the UDP checksum as
	 * HW cannot do checksum of UDP packets sent as multiple
	 * IP fragments.
	 */

	uh = udp_hdr(skb);
	iph = ip_hdr(skb);

	uh->check = 0;
	csum = skb_checksum(skb, 0, skb->len, 0);
	uh->check = udp_v4_check(skb->len, iph->saddr, iph->daddr, csum);
	if (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	/* If there is no outer header we can fake a checksum offload
	 * due to the fact that we have already done the checksum in
	 * software prior to segmenting the frame.
	 */
	if (!skb->encap_hdr_csum)
		features |= NETIF_F_HW_CSUM;

	/* Fragment the skb. IP headers of the fragments are updated in
	 * inet_gso_segment()
	 */
	segs = skb_segment(skb, features);
out:
	return segs;
}