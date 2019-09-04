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
struct sock {int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; int /*<<< orphan*/  ignore_df; } ;
struct rtable {int /*<<< orphan*/  dst; scalar_t__ rt_uses_gateway; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ttl; void* frag_off; } ;
struct TYPE_6__ {int optlen; scalar_t__ is_strictroute; int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_3__ opt; } ;
struct inet_sock {int /*<<< orphan*/  inet_daddr; int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_saddr; int /*<<< orphan*/  inet_opt; } ;
struct flowi4 {int dummy; } ;
struct TYPE_4__ {struct flowi4 ip4; } ;
struct flowi {TYPE_1__ u; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  void* __be16 ;
struct TYPE_5__ {scalar_t__ gso_segs; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 int IP_DF ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_CONN_FLAGS_TOS (struct sock*,int) ; 
 scalar_t__ __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_copy_addrs (struct iphdr*,struct flowi4*) ; 
 scalar_t__ ip_dont_fragment (struct sock*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_local_out (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_build (struct sk_buff*,TYPE_3__*,int /*<<< orphan*/ ,struct rtable*,int /*<<< orphan*/ ) ; 
 struct rtable* ip_route_output_ports (struct net*,struct flowi4*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_select_ident_segs (struct net*,struct sk_buff*,struct sock*,int) ; 
 int /*<<< orphan*/  ip_select_ttl (struct inet_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 struct net* sock_net (struct sock*) ; 

int __ip_queue_xmit(struct sock *sk, struct sk_buff *skb, struct flowi *fl,
		    __u8 tos)
{
	struct inet_sock *inet = inet_sk(sk);
	struct net *net = sock_net(sk);
	struct ip_options_rcu *inet_opt;
	struct flowi4 *fl4;
	struct rtable *rt;
	struct iphdr *iph;
	int res;

	/* Skip all of this if the packet is already routed,
	 * f.e. by something like SCTP.
	 */
	rcu_read_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	fl4 = &fl->u.ip4;
	rt = skb_rtable(skb);
	if (rt)
		goto packet_routed;

	/* Make sure we can route this packet. */
	rt = (struct rtable *)__sk_dst_check(sk, 0);
	if (!rt) {
		__be32 daddr;

		/* Use correct destination address if we have options. */
		daddr = inet->inet_daddr;
		if (inet_opt && inet_opt->opt.srr)
			daddr = inet_opt->opt.faddr;

		/* If this fails, retransmit mechanism of transport layer will
		 * keep trying until route appears or the connection times
		 * itself out.
		 */
		rt = ip_route_output_ports(net, fl4, sk,
					   daddr, inet->inet_saddr,
					   inet->inet_dport,
					   inet->inet_sport,
					   sk->sk_protocol,
					   RT_CONN_FLAGS_TOS(sk, tos),
					   sk->sk_bound_dev_if);
		if (IS_ERR(rt))
			goto no_route;
		sk_setup_caps(sk, &rt->dst);
	}
	skb_dst_set_noref(skb, &rt->dst);

packet_routed:
	if (inet_opt && inet_opt->opt.is_strictroute && rt->rt_uses_gateway)
		goto no_route;

	/* OK, we know where to send it, allocate and build IP header. */
	skb_push(skb, sizeof(struct iphdr) + (inet_opt ? inet_opt->opt.optlen : 0));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	*((__be16 *)iph) = htons((4 << 12) | (5 << 8) | (tos & 0xff));
	if (ip_dont_fragment(sk, &rt->dst) && !skb->ignore_df)
		iph->frag_off = htons(IP_DF);
	else
		iph->frag_off = 0;
	iph->ttl      = ip_select_ttl(inet, &rt->dst);
	iph->protocol = sk->sk_protocol;
	ip_copy_addrs(iph, fl4);

	/* Transport layer set skb->h.foo itself. */

	if (inet_opt && inet_opt->opt.optlen) {
		iph->ihl += inet_opt->opt.optlen >> 2;
		ip_options_build(skb, &inet_opt->opt, inet->inet_daddr, rt, 0);
	}

	ip_select_ident_segs(net, skb, sk,
			     skb_shinfo(skb)->gso_segs ?: 1);

	/* TODO : should we use skb->sk here instead of sk ? */
	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;

	res = ip_local_out(net, sk, skb);
	rcu_read_unlock();
	return res;

no_route:
	rcu_read_unlock();
	IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
	kfree_skb(skb);
	return -EHOSTUNREACH;
}