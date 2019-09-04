#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct udphdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct sock {int /*<<< orphan*/  sk_rx_dst; int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {scalar_t__ pkt_type; TYPE_1__* dev; int /*<<< orphan*/  destructor; struct sock* sk; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  protocol; } ;
struct in_device {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  inet_daddr; } ;
struct TYPE_5__ {int ifindex; } ;

/* Variables and functions */
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_MULTICAST ; 
 struct dst_entry* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (TYPE_1__*) ; 
 struct sock* __udp4_lib_demux_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sock* __udp4_lib_mcast_demux_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct net* dev_net (TYPE_1__*) ; 
 struct dst_entry* dst_check (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int inet_sdif (struct sk_buff*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int ip_check_mc_rcu (struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_mc_validate_source (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct in_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_efree ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

int udp_v4_early_demux(struct sk_buff *skb)
{
	struct net *net = dev_net(skb->dev);
	struct in_device *in_dev = NULL;
	const struct iphdr *iph;
	const struct udphdr *uh;
	struct sock *sk = NULL;
	struct dst_entry *dst;
	int dif = skb->dev->ifindex;
	int sdif = inet_sdif(skb);
	int ours;

	/* validate the packet */
	if (!pskb_may_pull(skb, skb_transport_offset(skb) + sizeof(struct udphdr)))
		return 0;

	iph = ip_hdr(skb);
	uh = udp_hdr(skb);

	if (skb->pkt_type == PACKET_MULTICAST) {
		in_dev = __in_dev_get_rcu(skb->dev);

		if (!in_dev)
			return 0;

		ours = ip_check_mc_rcu(in_dev, iph->daddr, iph->saddr,
				       iph->protocol);
		if (!ours)
			return 0;

		sk = __udp4_lib_mcast_demux_lookup(net, uh->dest, iph->daddr,
						   uh->source, iph->saddr,
						   dif, sdif);
	} else if (skb->pkt_type == PACKET_HOST) {
		sk = __udp4_lib_demux_lookup(net, uh->dest, iph->daddr,
					     uh->source, iph->saddr, dif, sdif);
	}

	if (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		return 0;

	skb->sk = sk;
	skb->destructor = sock_efree;
	dst = READ_ONCE(sk->sk_rx_dst);

	if (dst)
		dst = dst_check(dst, 0);
	if (dst) {
		u32 itag = 0;

		/* set noref for now.
		 * any place which wants to hold dst has to call
		 * dst_hold_safe()
		 */
		skb_dst_set_noref(skb, dst);

		/* for unconnected multicast sockets we need to validate
		 * the source on each packet
		 */
		if (!inet_sk(sk)->inet_daddr && in_dev)
			return ip_mc_validate_source(skb, iph->daddr,
						     iph->saddr, iph->tos,
						     skb->dev, in_dev, &itag);
	}
	return 0;
}