#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  protocol; } ;
struct neighbour {int type; } ;
struct dst_entry {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_7__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  broadcast; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int RTN_ANYCAST ; 
 int RTN_BROADCAST ; 
 int RTN_MULTICAST ; 
 int RTN_UNICAST ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct neighbour* dst_neigh_lookup_skb (struct dst_entry*,struct sk_buff*) ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int qeth_l3_get_cast_type(struct sk_buff *skb)
{
	struct neighbour *n = NULL;
	struct dst_entry *dst;

	rcu_read_lock();
	dst = skb_dst(skb);
	if (dst)
		n = dst_neigh_lookup_skb(dst, skb);
	if (n) {
		int cast_type = n->type;

		rcu_read_unlock();
		neigh_release(n);
		if ((cast_type == RTN_BROADCAST) ||
		    (cast_type == RTN_MULTICAST) ||
		    (cast_type == RTN_ANYCAST))
			return cast_type;
		return RTN_UNICAST;
	}
	rcu_read_unlock();

	/* no neighbour (eg AF_PACKET), fall back to target's IP address ... */
	if (be16_to_cpu(skb->protocol) == ETH_P_IPV6)
		return ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) ?
				RTN_MULTICAST : RTN_UNICAST;
	else if (be16_to_cpu(skb->protocol) == ETH_P_IP)
		return ipv4_is_multicast(ip_hdr(skb)->daddr) ?
				RTN_MULTICAST : RTN_UNICAST;

	/* ... and MAC address */
	if (ether_addr_equal_64bits(eth_hdr(skb)->h_dest, skb->dev->broadcast))
		return RTN_BROADCAST;
	if (is_multicast_ether_addr(eth_hdr(skb)->h_dest))
		return RTN_MULTICAST;

	/* default to unicast */
	return RTN_UNICAST;
}