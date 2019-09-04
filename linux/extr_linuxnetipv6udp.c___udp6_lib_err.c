#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct udp_table {int dummy; } ;
struct sock {scalar_t__ sk_state; int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {struct in6_addr daddr; struct in6_addr saddr; } ;
struct ipv6_pinfo {scalar_t__ pmtudisc; int /*<<< orphan*/  recverr; } ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_MIB_INERRORS ; 
 scalar_t__ ICMPV6_PKT_TOOBIG ; 
 scalar_t__ IPV6_PMTUDISC_DONT ; 
 scalar_t__ NDISC_REDIRECT ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  __ICMP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __in6_dev_get (int /*<<< orphan*/ ) ; 
 struct sock* __udp6_lib_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/ ,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udp_table*,struct sk_buff*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int icmpv6_err_convert (scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_accept_pmtu (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_redirect (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_update_pmtu (struct sk_buff*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_icmp_error (struct sock*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void __udp6_lib_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
		    u8 type, u8 code, int offset, __be32 info,
		    struct udp_table *udptable)
{
	struct ipv6_pinfo *np;
	const struct ipv6hdr *hdr = (const struct ipv6hdr *)skb->data;
	const struct in6_addr *saddr = &hdr->saddr;
	const struct in6_addr *daddr = &hdr->daddr;
	struct udphdr *uh = (struct udphdr *)(skb->data+offset);
	struct sock *sk;
	int harderr;
	int err;
	struct net *net = dev_net(skb->dev);

	sk = __udp6_lib_lookup(net, daddr, uh->dest, saddr, uh->source,
			       inet6_iif(skb), 0, udptable, skb);
	if (!sk) {
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev),
				  ICMP6_MIB_INERRORS);
		return;
	}

	harderr = icmpv6_err_convert(type, code, &err);
	np = inet6_sk(sk);

	if (type == ICMPV6_PKT_TOOBIG) {
		if (!ip6_sk_accept_pmtu(sk))
			goto out;
		ip6_sk_update_pmtu(skb, sk, info);
		if (np->pmtudisc != IPV6_PMTUDISC_DONT)
			harderr = 1;
	}
	if (type == NDISC_REDIRECT) {
		ip6_sk_redirect(skb, sk);
		goto out;
	}

	if (!np->recverr) {
		if (!harderr || sk->sk_state != TCP_ESTABLISHED)
			goto out;
	} else {
		ipv6_icmp_error(sk, skb, err, uh->dest, ntohl(info), (u8 *)(uh+1));
	}

	sk->sk_err = err;
	sk->sk_error_report(sk);
out:
	return;
}