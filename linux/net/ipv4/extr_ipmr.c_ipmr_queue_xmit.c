#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vif_device {int flags; TYPE_2__* dev; int /*<<< orphan*/  remote; int /*<<< orphan*/  local; int /*<<< orphan*/  bytes_out; int /*<<< orphan*/  pkt_out; int /*<<< orphan*/  link; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {scalar_t__ header_len; struct net_device* dev; } ;
struct rtable {TYPE_3__ dst; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {struct vif_device* vif_table; } ;
struct iphdr {int /*<<< orphan*/  frag_off; int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; } ;
struct flowi4 {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGMPMSG_WHOLEPKT ; 
 TYPE_5__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  IPSKB_FORWARDED ; 
 int /*<<< orphan*/  IPSTATS_MIB_FRAGFAILS ; 
 int IP_DF ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 scalar_t__ LL_RESERVED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_FORWARD ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int VIFF_REGISTER ; 
 int VIFF_TUNNEL ; 
 scalar_t__ dst_mtu (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_decrease_ttl (struct iphdr*) ; 
 int /*<<< orphan*/  ip_encap (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct rtable* ip_route_output_ports (struct net*,struct flowi4*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  ipmr_cache_report (struct mr_table*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmr_forward_finish ; 
 scalar_t__ ipmr_forward_offloaded (struct sk_buff*,struct mr_table*,int,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_3__*) ; 

__attribute__((used)) static void ipmr_queue_xmit(struct net *net, struct mr_table *mrt,
			    int in_vifi, struct sk_buff *skb, int vifi)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct vif_device *vif = &mrt->vif_table[vifi];
	struct net_device *dev;
	struct rtable *rt;
	struct flowi4 fl4;
	int    encap = 0;

	if (!vif->dev)
		goto out_free;

	if (vif->flags & VIFF_REGISTER) {
		vif->pkt_out++;
		vif->bytes_out += skb->len;
		vif->dev->stats.tx_bytes += skb->len;
		vif->dev->stats.tx_packets++;
		ipmr_cache_report(mrt, skb, vifi, IGMPMSG_WHOLEPKT);
		goto out_free;
	}

	if (ipmr_forward_offloaded(skb, mrt, in_vifi, vifi))
		goto out_free;

	if (vif->flags & VIFF_TUNNEL) {
		rt = ip_route_output_ports(net, &fl4, NULL,
					   vif->remote, vif->local,
					   0, 0,
					   IPPROTO_IPIP,
					   RT_TOS(iph->tos), vif->link);
		if (IS_ERR(rt))
			goto out_free;
		encap = sizeof(struct iphdr);
	} else {
		rt = ip_route_output_ports(net, &fl4, NULL, iph->daddr, 0,
					   0, 0,
					   IPPROTO_IPIP,
					   RT_TOS(iph->tos), vif->link);
		if (IS_ERR(rt))
			goto out_free;
	}

	dev = rt->dst.dev;

	if (skb->len+encap > dst_mtu(&rt->dst) && (ntohs(iph->frag_off) & IP_DF)) {
		/* Do not fragment multicasts. Alas, IPv4 does not
		 * allow to send ICMP, so that packets will disappear
		 * to blackhole.
		 */
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		ip_rt_put(rt);
		goto out_free;
	}

	encap += LL_RESERVED_SPACE(dev) + rt->dst.header_len;

	if (skb_cow(skb, encap)) {
		ip_rt_put(rt);
		goto out_free;
	}

	vif->pkt_out++;
	vif->bytes_out += skb->len;

	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);
	ip_decrease_ttl(ip_hdr(skb));

	/* FIXME: forward and output firewalls used to be called here.
	 * What do we do with netfilter? -- RR
	 */
	if (vif->flags & VIFF_TUNNEL) {
		ip_encap(net, skb, vif->local, vif->remote);
		/* FIXME: extra output firewall step used to be here. --RR */
		vif->dev->stats.tx_packets++;
		vif->dev->stats.tx_bytes += skb->len;
	}

	IPCB(skb)->flags |= IPSKB_FORWARDED;

	/* RFC1584 teaches, that DVMRP/PIM router must deliver packets locally
	 * not only before forwarding, but after forwarding on all output
	 * interfaces. It is clear, if mrouter runs a multicasting
	 * program, it should receive packets not depending to what interface
	 * program is joined.
	 * If we will not make it, the program will have to join on all
	 * interfaces. On the other hand, multihoming host (or router, but
	 * not mrouter) cannot join to more than one interface - it will
	 * result in receiving multiple packets.
	 */
	NF_HOOK(NFPROTO_IPV4, NF_INET_FORWARD,
		net, NULL, skb, skb->dev, dev,
		ipmr_forward_finish);
	return;

out_free:
	kfree_skb(skb);
}