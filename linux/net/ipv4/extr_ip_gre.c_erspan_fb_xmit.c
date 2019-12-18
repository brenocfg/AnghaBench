#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; scalar_t__ protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int mtu; int hard_header_len; TYPE_2__ stats; int /*<<< orphan*/  needed_headroom; } ;
struct ip_tunnel_key {int tun_flags; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; int options_len; struct ip_tunnel_key key; } ;
struct ip_tunnel {int /*<<< orphan*/  o_seqno; } ;
struct TYPE_10__ {int /*<<< orphan*/  dir; } ;
struct TYPE_6__ {TYPE_5__ md2; int /*<<< orphan*/  index; } ;
struct erspan_metadata {int version; TYPE_1__ u; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_9__ {int /*<<< orphan*/  tot_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ETH_P_ERSPAN ; 
 int /*<<< orphan*/  ETH_P_ERSPAN2 ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int IP_TUNNEL_INFO_TX ; 
 int TUNNEL_ERSPAN_OPT ; 
 int /*<<< orphan*/  TUNNEL_SEQ ; 
 int /*<<< orphan*/  erspan_build_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  erspan_build_header_v2 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int erspan_hdr_len (int) ; 
 int /*<<< orphan*/  get_hwid (TYPE_5__*) ; 
 int /*<<< orphan*/  gre_build_header (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gre_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_md_tunnel_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 struct erspan_metadata* ip_tunnel_info_opts (struct ip_tunnel_info*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void erspan_fb_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct ip_tunnel_info *tun_info;
	const struct ip_tunnel_key *key;
	struct erspan_metadata *md;
	bool truncate = false;
	__be16 proto;
	int tunnel_hlen;
	int version;
	int nhoff;
	int thoff;

	tun_info = skb_tunnel_info(skb);
	if (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		goto err_free_skb;

	key = &tun_info->key;
	if (!(tun_info->key.tun_flags & TUNNEL_ERSPAN_OPT))
		goto err_free_skb;
	if (tun_info->options_len < sizeof(*md))
		goto err_free_skb;
	md = ip_tunnel_info_opts(tun_info);

	/* ERSPAN has fixed 8 byte GRE header */
	version = md->version;
	tunnel_hlen = 8 + erspan_hdr_len(version);

	if (skb_cow_head(skb, dev->needed_headroom))
		goto err_free_skb;

	if (gre_handle_offloads(skb, false))
		goto err_free_skb;

	if (skb->len > dev->mtu + dev->hard_header_len) {
		pskb_trim(skb, dev->mtu + dev->hard_header_len);
		truncate = true;
	}

	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	if (skb->protocol == htons(ETH_P_IP) &&
	    (ntohs(ip_hdr(skb)->tot_len) > skb->len - nhoff))
		truncate = true;

	thoff = skb_transport_header(skb) - skb_mac_header(skb);
	if (skb->protocol == htons(ETH_P_IPV6) &&
	    (ntohs(ipv6_hdr(skb)->payload_len) > skb->len - thoff))
		truncate = true;

	if (version == 1) {
		erspan_build_header(skb, ntohl(tunnel_id_to_key32(key->tun_id)),
				    ntohl(md->u.index), truncate, true);
		proto = htons(ETH_P_ERSPAN);
	} else if (version == 2) {
		erspan_build_header_v2(skb,
				       ntohl(tunnel_id_to_key32(key->tun_id)),
				       md->u.md2.dir,
				       get_hwid(&md->u.md2),
				       truncate, true);
		proto = htons(ETH_P_ERSPAN2);
	} else {
		goto err_free_skb;
	}

	gre_build_header(skb, 8, TUNNEL_SEQ,
			 proto, 0, htonl(tunnel->o_seqno++));

	ip_md_tunnel_xmit(skb, dev, IPPROTO_GRE, tunnel_hlen);

	return;

err_free_skb:
	kfree_skb(skb);
	dev->stats.tx_dropped++;
}