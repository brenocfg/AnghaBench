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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtable {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;
struct ip_tunnel_key {int tun_flags; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; TYPE_2__ u; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; struct ip_tunnel_key key; } ;
struct ip_tunnel {int /*<<< orphan*/  o_seqno; } ;
struct flowi4 {int /*<<< orphan*/  saddr; } ;
typedef  int __be16 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  IP_DF ; 
 int IP_TUNNEL_INFO_TX ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int TUNNEL_KEY ; 
 int TUNNEL_SEQ ; 
 int /*<<< orphan*/  gre_build_header (struct sk_buff*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gre_calc_hlen (int) ; 
 scalar_t__ gre_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  iptunnel_xmit (int /*<<< orphan*/ ,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 struct rtable* prepare_fb_xmit (struct sk_buff*,struct net_device*,struct flowi4*,int) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gre_fb_xmit(struct sk_buff *skb, struct net_device *dev,
			__be16 proto)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct ip_tunnel_info *tun_info;
	const struct ip_tunnel_key *key;
	struct rtable *rt = NULL;
	struct flowi4 fl;
	int tunnel_hlen;
	__be16 df, flags;

	tun_info = skb_tunnel_info(skb);
	if (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		goto err_free_skb;

	key = &tun_info->key;
	tunnel_hlen = gre_calc_hlen(key->tun_flags);

	rt = prepare_fb_xmit(skb, dev, &fl, tunnel_hlen);
	if (!rt)
		return;

	/* Push Tunnel header. */
	if (gre_handle_offloads(skb, !!(tun_info->key.tun_flags & TUNNEL_CSUM)))
		goto err_free_rt;

	flags = tun_info->key.tun_flags &
		(TUNNEL_CSUM | TUNNEL_KEY | TUNNEL_SEQ);
	gre_build_header(skb, tunnel_hlen, flags, proto,
			 tunnel_id_to_key32(tun_info->key.tun_id),
			 (flags & TUNNEL_SEQ) ? htonl(tunnel->o_seqno++) : 0);

	df = key->tun_flags & TUNNEL_DONT_FRAGMENT ?  htons(IP_DF) : 0;

	iptunnel_xmit(skb->sk, rt, skb, fl.saddr, key->u.ipv4.dst, IPPROTO_GRE,
		      key->tos, key->ttl, df, false);
	return;

err_free_rt:
	ip_rt_put(rt);
err_free_skb:
	kfree_skb(skb);
	dev->stats.tx_dropped++;
}