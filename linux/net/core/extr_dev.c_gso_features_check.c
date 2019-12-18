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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ encapsulation; } ;
struct net_device {scalar_t__ gso_max_segs; int gso_partial_features; } ;
struct iphdr {int frag_off; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {scalar_t__ gso_segs; int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_DF ; 
 int NETIF_F_GSO_MASK ; 
 int NETIF_F_TSO_MANGLEID ; 
 int SKB_GSO_PARTIAL ; 
 int SKB_GSO_TCPV4 ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* inner_ip_hdr (struct sk_buff const*) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static netdev_features_t gso_features_check(const struct sk_buff *skb,
					    struct net_device *dev,
					    netdev_features_t features)
{
	u16 gso_segs = skb_shinfo(skb)->gso_segs;

	if (gso_segs > dev->gso_max_segs)
		return features & ~NETIF_F_GSO_MASK;

	/* Support for GSO partial features requires software
	 * intervention before we can actually process the packets
	 * so we need to strip support for any partial features now
	 * and we can pull them back in after we have partially
	 * segmented the frame.
	 */
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL))
		features &= ~dev->gso_partial_features;

	/* Make sure to clear the IPv4 ID mangling feature if the
	 * IPv4 header has the potential to be fragmented.
	 */
	if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4) {
		struct iphdr *iph = skb->encapsulation ?
				    inner_ip_hdr(skb) : ip_hdr(skb);

		if (!(iph->frag_off & htons(IP_DF)))
			features &= ~NETIF_F_TSO_MANGLEID;
	}

	return features;
}