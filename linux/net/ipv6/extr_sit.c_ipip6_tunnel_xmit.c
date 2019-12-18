#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int len; scalar_t__ sk; } ;
struct TYPE_7__ {struct net_device* dev; } ;
struct rtable {scalar_t__ rt_type; TYPE_3__ dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {int priv_flags; TYPE_1__ stats; } ;
struct neighbour {int /*<<< orphan*/  primary_key; } ;
struct in6_addr {scalar_t__* s6_addr32; } ;
struct ipv6hdr {int hop_limit; struct in6_addr daddr; } ;
struct iphdr {int tos; int ttl; scalar_t__ daddr; int /*<<< orphan*/  saddr; scalar_t__ frag_off; } ;
struct TYPE_6__ {struct iphdr iph; int /*<<< orphan*/  link; } ;
struct ip_tunnel {int hlen; scalar_t__ err_count; int /*<<< orphan*/  net; scalar_t__ err_time; TYPE_2__ parms; int /*<<< orphan*/  dst_cache; int /*<<< orphan*/  fwmark; } ;
struct flowi4 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_PKT_TOOBIG ; 
 int IFF_ISATAP ; 
 int INET_ECN_encapsulate (int,int) ; 
 int IPPROTO_IPV6 ; 
 scalar_t__ IPTUNNEL_ERR_TIMEO ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_COMPATv4 ; 
 int IPV6_ADDR_UNICAST ; 
 int IPV6_MIN_MTU ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int LL_RESERVED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ RTN_UNICAST ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TOS (int) ; 
 int /*<<< orphan*/  SKB_GSO_IPXIP4 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* dst_cache_get_ip4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_cache_set_ip4 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_link_failure (struct sk_buff*) ; 
 int dst_mtu (TYPE_3__*) ; 
 struct neighbour* dst_neigh_lookup (scalar_t__,struct in6_addr*) ; 
 int /*<<< orphan*/  flowi4_init_output (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rtable* ip_route_output_flow (int /*<<< orphan*/ ,struct flowi4*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 scalar_t__ ip_tunnel_encap (struct sk_buff*,struct ip_tunnel*,int*,struct flowi4*) ; 
 scalar_t__ iptunnel_handle_offloads (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iptunnel_xmit (int /*<<< orphan*/ *,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__,int) ; 
 scalar_t__ ipv6_addr_is_isatap (struct in6_addr const*) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 int ipv6_get_dsfield (struct ipv6hdr const*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_clone_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_update_pmtu (struct sk_buff*,int) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_inner_ipproto (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ try_6rd (struct ip_tunnel*,struct in6_addr*) ; 

__attribute__((used)) static netdev_tx_t ipip6_tunnel_xmit(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	const struct iphdr  *tiph = &tunnel->parms.iph;
	const struct ipv6hdr *iph6 = ipv6_hdr(skb);
	u8     tos = tunnel->parms.iph.tos;
	__be16 df = tiph->frag_off;
	struct rtable *rt;		/* Route to the other host */
	struct net_device *tdev;	/* Device to other host */
	unsigned int max_headroom;	/* The extra header space needed */
	__be32 dst = tiph->daddr;
	struct flowi4 fl4;
	int    mtu;
	const struct in6_addr *addr6;
	int addr_type;
	u8 ttl;
	u8 protocol = IPPROTO_IPV6;
	int t_hlen = tunnel->hlen + sizeof(struct iphdr);

	if (tos == 1)
		tos = ipv6_get_dsfield(iph6);

	/* ISATAP (RFC4214) - must come before 6to4 */
	if (dev->priv_flags & IFF_ISATAP) {
		struct neighbour *neigh = NULL;
		bool do_tx_error = false;

		if (skb_dst(skb))
			neigh = dst_neigh_lookup(skb_dst(skb), &iph6->daddr);

		if (!neigh) {
			net_dbg_ratelimited("nexthop == NULL\n");
			goto tx_error;
		}

		addr6 = (const struct in6_addr *)&neigh->primary_key;
		addr_type = ipv6_addr_type(addr6);

		if ((addr_type & IPV6_ADDR_UNICAST) &&
		     ipv6_addr_is_isatap(addr6))
			dst = addr6->s6_addr32[3];
		else
			do_tx_error = true;

		neigh_release(neigh);
		if (do_tx_error)
			goto tx_error;
	}

	if (!dst)
		dst = try_6rd(tunnel, &iph6->daddr);

	if (!dst) {
		struct neighbour *neigh = NULL;
		bool do_tx_error = false;

		if (skb_dst(skb))
			neigh = dst_neigh_lookup(skb_dst(skb), &iph6->daddr);

		if (!neigh) {
			net_dbg_ratelimited("nexthop == NULL\n");
			goto tx_error;
		}

		addr6 = (const struct in6_addr *)&neigh->primary_key;
		addr_type = ipv6_addr_type(addr6);

		if (addr_type == IPV6_ADDR_ANY) {
			addr6 = &ipv6_hdr(skb)->daddr;
			addr_type = ipv6_addr_type(addr6);
		}

		if ((addr_type & IPV6_ADDR_COMPATv4) != 0)
			dst = addr6->s6_addr32[3];
		else
			do_tx_error = true;

		neigh_release(neigh);
		if (do_tx_error)
			goto tx_error;
	}

	flowi4_init_output(&fl4, tunnel->parms.link, tunnel->fwmark,
			   RT_TOS(tos), RT_SCOPE_UNIVERSE, IPPROTO_IPV6,
			   0, dst, tiph->saddr, 0, 0,
			   sock_net_uid(tunnel->net, NULL));

	rt = dst_cache_get_ip4(&tunnel->dst_cache, &fl4.saddr);
	if (!rt) {
		rt = ip_route_output_flow(tunnel->net, &fl4, NULL);
		if (IS_ERR(rt)) {
			dev->stats.tx_carrier_errors++;
			goto tx_error_icmp;
		}
		dst_cache_set_ip4(&tunnel->dst_cache, &rt->dst, fl4.saddr);
	}

	if (rt->rt_type != RTN_UNICAST) {
		ip_rt_put(rt);
		dev->stats.tx_carrier_errors++;
		goto tx_error_icmp;
	}
	tdev = rt->dst.dev;

	if (tdev == dev) {
		ip_rt_put(rt);
		dev->stats.collisions++;
		goto tx_error;
	}

	if (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP4)) {
		ip_rt_put(rt);
		goto tx_error;
	}

	if (df) {
		mtu = dst_mtu(&rt->dst) - t_hlen;

		if (mtu < 68) {
			dev->stats.collisions++;
			ip_rt_put(rt);
			goto tx_error;
		}

		if (mtu < IPV6_MIN_MTU) {
			mtu = IPV6_MIN_MTU;
			df = 0;
		}

		if (tunnel->parms.iph.daddr)
			skb_dst_update_pmtu(skb, mtu);

		if (skb->len > mtu && !skb_is_gso(skb)) {
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			ip_rt_put(rt);
			goto tx_error;
		}
	}

	if (tunnel->err_count > 0) {
		if (time_before(jiffies,
				tunnel->err_time + IPTUNNEL_ERR_TIMEO)) {
			tunnel->err_count--;
			dst_link_failure(skb);
		} else
			tunnel->err_count = 0;
	}

	/*
	 * Okay, now see if we can stuff it in the buffer as-is.
	 */
	max_headroom = LL_RESERVED_SPACE(tdev) + t_hlen;

	if (skb_headroom(skb) < max_headroom || skb_shared(skb) ||
	    (skb_cloned(skb) && !skb_clone_writable(skb, 0))) {
		struct sk_buff *new_skb = skb_realloc_headroom(skb, max_headroom);
		if (!new_skb) {
			ip_rt_put(rt);
			dev->stats.tx_dropped++;
			kfree_skb(skb);
			return NETDEV_TX_OK;
		}
		if (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		dev_kfree_skb(skb);
		skb = new_skb;
		iph6 = ipv6_hdr(skb);
	}
	ttl = tiph->ttl;
	if (ttl == 0)
		ttl = iph6->hop_limit;
	tos = INET_ECN_encapsulate(tos, ipv6_get_dsfield(iph6));

	if (ip_tunnel_encap(skb, tunnel, &protocol, &fl4) < 0) {
		ip_rt_put(rt);
		goto tx_error;
	}

	skb_set_inner_ipproto(skb, IPPROTO_IPV6);

	iptunnel_xmit(NULL, rt, skb, fl4.saddr, fl4.daddr, protocol, tos, ttl,
		      df, !net_eq(tunnel->net, dev_net(dev)));
	return NETDEV_TX_OK;

tx_error_icmp:
	dst_link_failure(skb);
tx_error:
	kfree_skb(skb);
	dev->stats.tx_errors++;
	return NETDEV_TX_OK;
}