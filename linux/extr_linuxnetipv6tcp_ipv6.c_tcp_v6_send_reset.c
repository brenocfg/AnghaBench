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
typedef  scalar_t__ u32 ;
struct tcphdr {int doff; scalar_t__ fin; scalar_t__ syn; int /*<<< orphan*/  seq; int /*<<< orphan*/  ack_seq; scalar_t__ ack; scalar_t__ rst; } ;
struct tcp_md5sig_key {int dummy; } ;
struct sock {int sk_bound_dev_if; } ;
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_fullsock (struct sock const*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_send_response (struct sock const*,struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tcp_md5sig_key*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tcp_send_reset (struct sock const*,struct sk_buff*) ; 

__attribute__((used)) static void tcp_v6_send_reset(const struct sock *sk, struct sk_buff *skb)
{
	const struct tcphdr *th = tcp_hdr(skb);
	u32 seq = 0, ack_seq = 0;
	struct tcp_md5sig_key *key = NULL;
#ifdef CONFIG_TCP_MD5SIG
	const __u8 *hash_location = NULL;
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	unsigned char newhash[16];
	int genhash;
	struct sock *sk1 = NULL;
#endif
	int oif = 0;

	if (th->rst)
		return;

	/* If sk not NULL, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
	if (!sk && !ipv6_unicast_destination(skb))
		return;

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
		sk1 = inet6_lookup_listener(dev_net(skb_dst(skb)->dev),
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
		if (sk_fullsock(sk))
			trace_tcp_send_reset(sk, skb);
	}

	tcp_v6_send_response(sk, skb, seq, ack_seq, 0, 0, 0, oif, key, 1, 0, 0);

#ifdef CONFIG_TCP_MD5SIG
out:
	rcu_read_unlock();
#endif
}