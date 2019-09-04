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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  priority; int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; scalar_t__ header_len; } ;
struct rtable {TYPE_2__ dst; scalar_t__ rt_uses_gateway; } ;
struct TYPE_4__ {scalar_t__ sysctl_ip_fwd_update_priority; } ;
struct net {TYPE_1__ ipv4; } ;
struct iphdr {int ttl; int /*<<< orphan*/  tos; } ;
struct ip_options {int /*<<< orphan*/  srr; scalar_t__ is_strictroute; scalar_t__ router_alert; } ;
struct TYPE_6__ {int flags; struct ip_options opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_EXC_TTL ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 int /*<<< orphan*/  ICMP_SR_FAILED ; 
 int /*<<< orphan*/  ICMP_TIME_EXCEEDED ; 
 TYPE_3__* IPCB (struct sk_buff*) ; 
 int IPSKB_DOREDIRECT ; 
 int IPSKB_FORWARDED ; 
 int /*<<< orphan*/  IPSTATS_MIB_FRAGFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ LL_RESERVED_SPACE (int /*<<< orphan*/ ) ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_FORWARD ; 
 scalar_t__ PACKET_HOST ; 
 int /*<<< orphan*/  XFRM_POLICY_FWD ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_call_ra_chain (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_decrease_ttl (struct iphdr*) ; 
 int /*<<< orphan*/  ip_dst_mtu_maybe_forward (TYPE_2__*,int) ; 
 scalar_t__ ip_exceeds_mtu (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_forward_finish ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_rt_send_redirect (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rt_tos2priority (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_forward_csum (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_sec_path (struct sk_buff*) ; 
 scalar_t__ skb_warn_if_lro (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm4_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm4_route_forward (struct sk_buff*) ; 

int ip_forward(struct sk_buff *skb)
{
	u32 mtu;
	struct iphdr *iph;	/* Our header */
	struct rtable *rt;	/* Route we use */
	struct ip_options *opt	= &(IPCB(skb)->opt);
	struct net *net;

	/* that should never happen */
	if (skb->pkt_type != PACKET_HOST)
		goto drop;

	if (unlikely(skb->sk))
		goto drop;

	if (skb_warn_if_lro(skb))
		goto drop;

	if (!xfrm4_policy_check(NULL, XFRM_POLICY_FWD, skb))
		goto drop;

	if (IPCB(skb)->opt.router_alert && ip_call_ra_chain(skb))
		return NET_RX_SUCCESS;

	skb_forward_csum(skb);
	net = dev_net(skb->dev);

	/*
	 *	According to the RFC, we must first decrease the TTL field. If
	 *	that reaches zero, we must reply an ICMP control message telling
	 *	that the packet's lifetime expired.
	 */
	if (ip_hdr(skb)->ttl <= 1)
		goto too_many_hops;

	if (!xfrm4_route_forward(skb))
		goto drop;

	rt = skb_rtable(skb);

	if (opt->is_strictroute && rt->rt_uses_gateway)
		goto sr_failed;

	IPCB(skb)->flags |= IPSKB_FORWARDED;
	mtu = ip_dst_mtu_maybe_forward(&rt->dst, true);
	if (ip_exceeds_mtu(skb, mtu)) {
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			  htonl(mtu));
		goto drop;
	}

	/* We are about to mangle packet. Copy it! */
	if (skb_cow(skb, LL_RESERVED_SPACE(rt->dst.dev)+rt->dst.header_len))
		goto drop;
	iph = ip_hdr(skb);

	/* Decrease ttl after skb cow done */
	ip_decrease_ttl(iph);

	/*
	 *	We now generate an ICMP HOST REDIRECT giving the route
	 *	we calculated.
	 */
	if (IPCB(skb)->flags & IPSKB_DOREDIRECT && !opt->srr &&
	    !skb_sec_path(skb))
		ip_rt_send_redirect(skb);

	if (net->ipv4.sysctl_ip_fwd_update_priority)
		skb->priority = rt_tos2priority(iph->tos);

	return NF_HOOK(NFPROTO_IPV4, NF_INET_FORWARD,
		       net, NULL, skb, skb->dev, rt->dst.dev,
		       ip_forward_finish);

sr_failed:
	/*
	 *	Strict routing permits no gatewaying
	 */
	 icmp_send(skb, ICMP_DEST_UNREACH, ICMP_SR_FAILED, 0);
	 goto drop;

too_many_hops:
	/* Tell the sender its packet died... */
	__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
	icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, 0);
drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}