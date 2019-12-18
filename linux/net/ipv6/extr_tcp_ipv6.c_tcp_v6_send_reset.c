#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tcphdr {int doff; scalar_t__ fin; scalar_t__ syn; int /*<<< orphan*/  seq; int /*<<< orphan*/  ack_seq; scalar_t__ ack; int /*<<< orphan*/  source; scalar_t__ rst; } ;
struct tcp_md5sig_key {int dummy; } ;
typedef  struct sock {int sk_bound_dev_if; scalar_t__ sk_state; scalar_t__ sk_priority; } const sock ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_5__ {int flowlabel_reflect; } ;
struct TYPE_6__ {TYPE_1__ sysctl; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ipv6_pinfo {scalar_t__ repflow; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {scalar_t__ tw_priority; int /*<<< orphan*/  tw_flowlabel; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FLOWLABEL_REFLECT_TCP_RESET ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct sock const* inet6_lookup_listener (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* inet_twsk (struct sock const*) ; 
 int /*<<< orphan*/  ip6_flowlabel (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ sk_fullsock (struct sock const*) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 struct net* sock_net (struct sock const*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 struct ipv6_pinfo* tcp_inet6_sk (struct sock const*) ; 
 int /*<<< orphan*/ * tcp_parse_md5sig_option (struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_v6_iif_l3_slave (struct sk_buff*) ; 
 struct tcp_md5sig_key* tcp_v6_md5_do_lookup (struct sock const*,int /*<<< orphan*/ *) ; 
 int tcp_v6_md5_hash_skb (unsigned char*,struct tcp_md5sig_key*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_sdif (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_send_response (struct sock const*,struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tcp_md5sig_key*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_tcp_send_reset (struct sock const*,struct sk_buff*) ; 

__attribute__((used)) static void tcp_v6_send_reset(const struct sock *sk, struct sk_buff *skb)
{
	const struct tcphdr *th = tcp_hdr(skb);
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	u32 seq = 0, ack_seq = 0;
	struct tcp_md5sig_key *key = NULL;
#ifdef CONFIG_TCP_MD5SIG
	const __u8 *hash_location = NULL;
	unsigned char newhash[16];
	int genhash;
	struct sock *sk1 = NULL;
#endif
	__be32 label = 0;
	u32 priority = 0;
	struct net *net;
	int oif = 0;

	if (th->rst)
		return;

	/* If sk not NULL, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
	if (!sk && !ipv6_unicast_destination(skb))
		return;

	net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
#ifdef CONFIG_TCP_MD5SIG
	rcu_read_lock();
	hash_location = tcp_parse_md5sig_option(th);
	if (sk && sk_fullsock(sk)) {
		key = tcp_v6_md5_do_lookup(sk, &ipv6h->saddr);
	} else if (hash_location) {
		/*
		 * active side is lost. Try to find listening socket through
		 * source port, and then find md5 key through listening socket.
		 * we are not loose security here:
		 * Incoming packet is checked with md5 hash with finding key,
		 * no RST generated if md5 hash doesn't match.
		 */
		sk1 = inet6_lookup_listener(net,
					   &tcp_hashinfo, NULL, 0,
					   &ipv6h->saddr,
					   th->source, &ipv6h->daddr,
					   ntohs(th->source),
					   tcp_v6_iif_l3_slave(skb),
					   tcp_v6_sdif(skb));
		if (!sk1)
			goto out;

		key = tcp_v6_md5_do_lookup(sk1, &ipv6h->saddr);
		if (!key)
			goto out;

		genhash = tcp_v6_md5_hash_skb(newhash, key, NULL, skb);
		if (genhash || memcmp(hash_location, newhash, 16) != 0)
			goto out;
	}
#endif

	if (th->ack)
		seq = ntohl(th->ack_seq);
	else
		ack_seq = ntohl(th->seq) + th->syn + th->fin + skb->len -
			  (th->doff << 2);

	if (sk) {
		oif = sk->sk_bound_dev_if;
		if (sk_fullsock(sk)) {
			const struct ipv6_pinfo *np = tcp_inet6_sk(sk);

			trace_tcp_send_reset(sk, skb);
			if (np->repflow)
				label = ip6_flowlabel(ipv6h);
			priority = sk->sk_priority;
		}
		if (sk->sk_state == TCP_TIME_WAIT) {
			label = cpu_to_be32(inet_twsk(sk)->tw_flowlabel);
			priority = inet_twsk(sk)->tw_priority;
		}
	} else {
		if (net->ipv6.sysctl.flowlabel_reflect & FLOWLABEL_REFLECT_TCP_RESET)
			label = ip6_flowlabel(ipv6h);
	}

	tcp_v6_send_response(sk, skb, seq, ack_seq, 0, 0, 0, oif, key, 1, 0,
			     label, priority);

#ifdef CONFIG_TCP_MD5SIG
out:
	rcu_read_unlock();
#endif
}