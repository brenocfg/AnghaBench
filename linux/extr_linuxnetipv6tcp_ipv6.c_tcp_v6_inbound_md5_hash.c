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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool tcp_v6_inbound_md5_hash(const struct sock *sk,
				    const struct sk_buff *skb)
{
#ifdef CONFIG_TCP_MD5SIG
	const __u8 *hash_location = NULL;
	struct tcp_md5sig_key *hash_expected;
	const struct ipv6hdr *ip6h = ipv6_hdr(skb);
	const struct tcphdr *th = tcp_hdr(skb);
	int genhash;
	u8 newhash[16];

	hash_expected = tcp_v6_md5_do_lookup(sk, &ip6h->saddr);
	hash_location = tcp_parse_md5sig_option(th);

	/* We've parsed the options - do we have a hash? */
	if (!hash_expected && !hash_location)
		return false;

	if (hash_expected && !hash_location) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5NOTFOUND);
		return true;
	}

	if (!hash_expected && hash_location) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5UNEXPECTED);
		return true;
	}

	/* check the signature */
	genhash = tcp_v6_md5_hash_skb(newhash,
				      hash_expected,
				      NULL, skb);

	if (genhash || memcmp(hash_location, newhash, 16) != 0) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMD5FAILURE);
		net_info_ratelimited("MD5 Hash %s for [%pI6c]:%u->[%pI6c]:%u\n",
				     genhash ? "failed" : "mismatch",
				     &ip6h->saddr, ntohs(th->source),
				     &ip6h->daddr, ntohs(th->dest));
		return true;
	}
#endif
	return false;
}