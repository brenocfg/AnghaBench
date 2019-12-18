#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct net_device {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_8__ {TYPE_1__ ipv6; } ;
struct ip_tunnel_key {int /*<<< orphan*/  tos; int /*<<< orphan*/  label; TYPE_2__ u; } ;
struct ip_tunnel_info {int mode; struct ip_tunnel_key key; } ;
struct TYPE_11__ {int flags; int encap_limit; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  flowinfo; scalar_t__ collect_md; int /*<<< orphan*/  proto; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip6; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct ip6_tnl {TYPE_5__ parms; TYPE_4__ fl; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  flowi6_mark; scalar_t__ flowi6_proto; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  fl6 ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_12__ {struct flowi6 opt; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 int /*<<< orphan*/  INET_ECN_encapsulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP6_TNL_F_IGN_ENCAP_LIMIT ; 
 int IP6_TNL_F_USE_ORIG_FWMARK ; 
 int IP6_TNL_F_USE_ORIG_TCLASS ; 
 TYPE_6__* IPCB (struct sk_buff*) ; 
 scalar_t__ IPPROTO_IPIP ; 
 int IP_TUNNEL_INFO_TX ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKB_GSO_IPXIP6 ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_tclass (int /*<<< orphan*/ ) ; 
 int ip6_tnl_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,struct flowi6*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 scalar_t__ iptunnel_handle_offloads (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_get_dsfield (struct iphdr const*) ; 
 int /*<<< orphan*/  memcpy (struct flowi6*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_set_inner_ipproto (struct sk_buff*,scalar_t__) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
ip4ip6_tnl_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	const struct iphdr  *iph;
	int encap_limit = -1;
	struct flowi6 fl6;
	__u8 dsfield;
	__u32 mtu;
	u8 tproto;
	int err;

	iph = ip_hdr(skb);
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	tproto = READ_ONCE(t->parms.proto);
	if (tproto != IPPROTO_IPIP && tproto != 0)
		return -1;

	if (t->parms.collect_md) {
		struct ip_tunnel_info *tun_info;
		const struct ip_tunnel_key *key;

		tun_info = skb_tunnel_info(skb);
		if (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
			     ip_tunnel_info_af(tun_info) != AF_INET6))
			return -1;
		key = &tun_info->key;
		memset(&fl6, 0, sizeof(fl6));
		fl6.flowi6_proto = IPPROTO_IPIP;
		fl6.saddr = key->u.ipv6.src;
		fl6.daddr = key->u.ipv6.dst;
		fl6.flowlabel = key->label;
		dsfield =  key->tos;
	} else {
		if (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
			encap_limit = t->parms.encap_limit;

		memcpy(&fl6, &t->fl.u.ip6, sizeof(fl6));
		fl6.flowi6_proto = IPPROTO_IPIP;

		if (t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS)
			dsfield = ipv4_get_dsfield(iph);
		else
			dsfield = ip6_tclass(t->parms.flowinfo);
		if (t->parms.flags & IP6_TNL_F_USE_ORIG_FWMARK)
			fl6.flowi6_mark = skb->mark;
		else
			fl6.flowi6_mark = t->parms.fwmark;
	}

	fl6.flowi6_uid = sock_net_uid(dev_net(dev), NULL);
	dsfield = INET_ECN_encapsulate(dsfield, ipv4_get_dsfield(iph));

	if (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP6))
		return -1;

	skb_set_inner_ipproto(skb, IPPROTO_IPIP);

	err = ip6_tnl_xmit(skb, dev, dsfield, &fl6, encap_limit, &mtu,
			   IPPROTO_IPIP);
	if (err != 0) {
		/* XXX: send ICMP error even if DF is not set. */
		if (err == -EMSGSIZE)
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				  htonl(mtu));
		return -1;
	}

	return 0;
}