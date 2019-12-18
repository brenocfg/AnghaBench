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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  needed_headroom; } ;
struct ip_tunnel_key {int tun_flags; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; struct ip_tunnel_key key; } ;
struct ip_tunnel {int /*<<< orphan*/  o_seqno; } ;
typedef  int __be16 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int IP_TUNNEL_INFO_TX ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_KEY ; 
 int TUNNEL_SEQ ; 
 int /*<<< orphan*/  gre_build_header (struct sk_buff*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gre_calc_hlen (int) ; 
 scalar_t__ gre_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_md_tunnel_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gre_fb_xmit(struct sk_buff *skb, struct net_device *dev,
			__be16 proto)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct ip_tunnel_info *tun_info;
	const struct ip_tunnel_key *key;
	int tunnel_hlen;
	__be16 flags;

	tun_info = skb_tunnel_info(skb);
	if (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		goto err_free_skb;

	key = &tun_info->key;
	tunnel_hlen = gre_calc_hlen(key->tun_flags);

	if (skb_cow_head(skb, dev->needed_headroom))
		goto err_free_skb;

	/* Push Tunnel header. */
	if (gre_handle_offloads(skb, !!(tun_info->key.tun_flags & TUNNEL_CSUM)))
		goto err_free_skb;

	flags = tun_info->key.tun_flags &
		(TUNNEL_CSUM | TUNNEL_KEY | TUNNEL_SEQ);
	gre_build_header(skb, tunnel_hlen, flags, proto,
			 tunnel_id_to_key32(tun_info->key.tun_id),
			 (flags & TUNNEL_SEQ) ? htonl(tunnel->o_seqno++) : 0);

	ip_md_tunnel_xmit(skb, dev, IPPROTO_GRE, tunnel_hlen);

	return;

err_free_skb:
	kfree_skb(skb);
	dev->stats.tx_dropped++;
}