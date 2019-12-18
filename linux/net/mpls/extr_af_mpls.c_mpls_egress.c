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
typedef  int u8 ;
struct sk_buff {void* protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_ttl_propagate; } ;
struct net {TYPE_1__ mpls; } ;
struct mpls_route {int rt_payload_type; int /*<<< orphan*/  rt_ttl_propagate; } ;
struct mpls_entry_decoded {int ttl; } ;
struct ipv6hdr {int hop_limit; } ;
struct iphdr {int version; int ttl; int /*<<< orphan*/  check; } ;
typedef  enum mpls_payload_type { ____Placeholder_mpls_payload_type } mpls_payload_type ;

/* Variables and functions */
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_DEFAULT ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_ENABLED ; 
#define  MPT_IPV4 130 
#define  MPT_IPV6 129 
#define  MPT_UNSPEC 128 
 int /*<<< orphan*/  csum_replace2 (int /*<<< orphan*/ *,void*,void*) ; 
 void* htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static bool mpls_egress(struct net *net, struct mpls_route *rt,
			struct sk_buff *skb, struct mpls_entry_decoded dec)
{
	enum mpls_payload_type payload_type;
	bool success = false;

	/* The IPv4 code below accesses through the IPv4 header
	 * checksum, which is 12 bytes into the packet.
	 * The IPv6 code below accesses through the IPv6 hop limit
	 * which is 8 bytes into the packet.
	 *
	 * For all supported cases there should always be at least 12
	 * bytes of packet data present.  The IPv4 header is 20 bytes
	 * without options and the IPv6 header is always 40 bytes
	 * long.
	 */
	if (!pskb_may_pull(skb, 12))
		return false;

	payload_type = rt->rt_payload_type;
	if (payload_type == MPT_UNSPEC)
		payload_type = ip_hdr(skb)->version;

	switch (payload_type) {
	case MPT_IPV4: {
		struct iphdr *hdr4 = ip_hdr(skb);
		u8 new_ttl;
		skb->protocol = htons(ETH_P_IP);

		/* If propagating TTL, take the decremented TTL from
		 * the incoming MPLS header, otherwise decrement the
		 * TTL, but only if not 0 to avoid underflow.
		 */
		if (rt->rt_ttl_propagate == MPLS_TTL_PROP_ENABLED ||
		    (rt->rt_ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
		     net->mpls.ip_ttl_propagate))
			new_ttl = dec.ttl;
		else
			new_ttl = hdr4->ttl ? hdr4->ttl - 1 : 0;

		csum_replace2(&hdr4->check,
			      htons(hdr4->ttl << 8),
			      htons(new_ttl << 8));
		hdr4->ttl = new_ttl;
		success = true;
		break;
	}
	case MPT_IPV6: {
		struct ipv6hdr *hdr6 = ipv6_hdr(skb);
		skb->protocol = htons(ETH_P_IPV6);

		/* If propagating TTL, take the decremented TTL from
		 * the incoming MPLS header, otherwise decrement the
		 * hop limit, but only if not 0 to avoid underflow.
		 */
		if (rt->rt_ttl_propagate == MPLS_TTL_PROP_ENABLED ||
		    (rt->rt_ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
		     net->mpls.ip_ttl_propagate))
			hdr6->hop_limit = dec.ttl;
		else if (hdr6->hop_limit)
			hdr6->hop_limit = hdr6->hop_limit - 1;
		success = true;
		break;
	}
	case MPT_UNSPEC:
		/* Should have decided which protocol it is by now */
		break;
	}

	return success;
}