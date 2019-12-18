#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int protocol; int /*<<< orphan*/  mark; } ;
struct TYPE_12__ {scalar_t__ header_len; struct net_device* dev; } ;
struct rtable {TYPE_5__ dst; } ;
struct TYPE_11__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {scalar_t__ needed_headroom; TYPE_4__ stats; } ;
struct ipv6hdr {int hop_limit; } ;
struct iphdr {int tos; int ttl; int frag_off; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_10__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int tos; int tun_flags; int ttl; TYPE_3__ u; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; int /*<<< orphan*/  dst_cache; struct ip_tunnel_key key; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct ip_tunnel {int /*<<< orphan*/  net; TYPE_1__ encap; } ;
struct flowi4 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int __be16 ;
struct TYPE_13__ {int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_7__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP_DF ; 
 int IP_TUNNEL_INFO_TX ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 scalar_t__ LL_RESERVED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/  RT_TOS (int) ; 
 int TUNNEL_DONT_FRAGMENT ; 
 scalar_t__ TUNNEL_ENCAP_NONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* dst_cache_get_ip4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_cache_set_ip4 (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int ip4_dst_hoplimit (TYPE_5__*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int ip_tunnel_dst_cache_usable (struct sk_buff*,struct ip_tunnel_info*) ; 
 int ip_tunnel_ecn_encap (int,struct iphdr const*,struct sk_buff*) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  ip_tunnel_init_flow (struct flowi4*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iptunnel_xmit (int /*<<< orphan*/ *,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int ipv6_get_dsfield (struct ipv6hdr const*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_get_hash (struct sk_buff*) ; 
 scalar_t__ skb_inner_network_header (struct sk_buff*) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 scalar_t__ tnl_update_pmtu (struct net_device*,struct sk_buff*,struct rtable*,int,struct iphdr const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void ip_md_tunnel_xmit(struct sk_buff *skb, struct net_device *dev,
		       u8 proto, int tunnel_hlen)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	u32 headroom = sizeof(struct iphdr);
	struct ip_tunnel_info *tun_info;
	const struct ip_tunnel_key *key;
	const struct iphdr *inner_iph;
	struct rtable *rt = NULL;
	struct flowi4 fl4;
	__be16 df = 0;
	u8 tos, ttl;
	bool use_cache;

	tun_info = skb_tunnel_info(skb);
	if (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		goto tx_error;
	key = &tun_info->key;
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	inner_iph = (const struct iphdr *)skb_inner_network_header(skb);
	tos = key->tos;
	if (tos == 1) {
		if (skb->protocol == htons(ETH_P_IP))
			tos = inner_iph->tos;
		else if (skb->protocol == htons(ETH_P_IPV6))
			tos = ipv6_get_dsfield((const struct ipv6hdr *)inner_iph);
	}
	ip_tunnel_init_flow(&fl4, proto, key->u.ipv4.dst, key->u.ipv4.src,
			    tunnel_id_to_key32(key->tun_id), RT_TOS(tos),
			    0, skb->mark, skb_get_hash(skb));
	if (tunnel->encap.type != TUNNEL_ENCAP_NONE)
		goto tx_error;

	use_cache = ip_tunnel_dst_cache_usable(skb, tun_info);
	if (use_cache)
		rt = dst_cache_get_ip4(&tun_info->dst_cache, &fl4.saddr);
	if (!rt) {
		rt = ip_route_output_key(tunnel->net, &fl4);
		if (IS_ERR(rt)) {
			dev->stats.tx_carrier_errors++;
			goto tx_error;
		}
		if (use_cache)
			dst_cache_set_ip4(&tun_info->dst_cache, &rt->dst,
					  fl4.saddr);
	}
	if (rt->dst.dev == dev) {
		ip_rt_put(rt);
		dev->stats.collisions++;
		goto tx_error;
	}

	if (key->tun_flags & TUNNEL_DONT_FRAGMENT)
		df = htons(IP_DF);
	if (tnl_update_pmtu(dev, skb, rt, df, inner_iph, tunnel_hlen,
			    key->u.ipv4.dst, true)) {
		ip_rt_put(rt);
		goto tx_error;
	}

	tos = ip_tunnel_ecn_encap(tos, inner_iph, skb);
	ttl = key->ttl;
	if (ttl == 0) {
		if (skb->protocol == htons(ETH_P_IP))
			ttl = inner_iph->ttl;
		else if (skb->protocol == htons(ETH_P_IPV6))
			ttl = ((const struct ipv6hdr *)inner_iph)->hop_limit;
		else
			ttl = ip4_dst_hoplimit(&rt->dst);
	}

	if (!df && skb->protocol == htons(ETH_P_IP))
		df = inner_iph->frag_off & htons(IP_DF);

	headroom += LL_RESERVED_SPACE(rt->dst.dev) + rt->dst.header_len;
	if (headroom > dev->needed_headroom)
		dev->needed_headroom = headroom;

	if (skb_cow_head(skb, dev->needed_headroom)) {
		ip_rt_put(rt);
		goto tx_dropped;
	}
	iptunnel_xmit(NULL, rt, skb, fl4.saddr, fl4.daddr, proto, tos, ttl,
		      df, !net_eq(tunnel->net, dev_net(dev)));
	return;
tx_error:
	dev->stats.tx_errors++;
	goto kfree;
tx_dropped:
	dev->stats.tx_dropped++;
kfree:
	kfree_skb(skb);
}