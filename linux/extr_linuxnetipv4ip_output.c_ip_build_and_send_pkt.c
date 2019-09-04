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
struct sock {scalar_t__ sk_mark; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_protocol; } ;
struct sk_buff {int /*<<< orphan*/  sk; scalar_t__ mark; int /*<<< orphan*/  priority; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct net {int dummy; } ;
struct iphdr {int version; int ihl; scalar_t__ frag_off; scalar_t__ id; int /*<<< orphan*/  protocol; void* saddr; void* daddr; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_2__ {int optlen; void* faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct inet_sock {int /*<<< orphan*/  tos; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  __ip_select_ident (struct net*,struct iphdr*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 scalar_t__ ip_dont_fragment (struct sock const*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_local_out (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_build (struct sk_buff*,TYPE_1__*,void*,struct rtable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_select_ttl (struct inet_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 struct net* sock_net (struct sock const*) ; 

int ip_build_and_send_pkt(struct sk_buff *skb, const struct sock *sk,
			  __be32 saddr, __be32 daddr, struct ip_options_rcu *opt)
{
	struct inet_sock *inet = inet_sk(sk);
	struct rtable *rt = skb_rtable(skb);
	struct net *net = sock_net(sk);
	struct iphdr *iph;

	/* Build the IP header. */
	skb_push(skb, sizeof(struct iphdr) + (opt ? opt->opt.optlen : 0));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	iph->version  = 4;
	iph->ihl      = 5;
	iph->tos      = inet->tos;
	iph->ttl      = ip_select_ttl(inet, &rt->dst);
	iph->daddr    = (opt && opt->opt.srr ? opt->opt.faddr : daddr);
	iph->saddr    = saddr;
	iph->protocol = sk->sk_protocol;
	if (ip_dont_fragment(sk, &rt->dst)) {
		iph->frag_off = htons(IP_DF);
		iph->id = 0;
	} else {
		iph->frag_off = 0;
		__ip_select_ident(net, iph, 1);
	}

	if (opt && opt->opt.optlen) {
		iph->ihl += opt->opt.optlen>>2;
		ip_options_build(skb, &opt->opt, daddr, rt, 0);
	}

	skb->priority = sk->sk_priority;
	if (!skb->mark)
		skb->mark = sk->sk_mark;

	/* Send it out. */
	return ip_local_out(net, skb->sk, skb);
}