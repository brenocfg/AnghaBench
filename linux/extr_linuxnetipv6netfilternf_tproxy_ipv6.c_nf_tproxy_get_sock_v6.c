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
typedef  int u8 ;
struct tcphdr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_v6_rcv_saddr; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  enum nf_tproxy_lookup_t { ____Placeholder_nf_tproxy_lookup_t } nf_tproxy_lookup_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  IPPROTO_TCP 131 
#define  IPPROTO_UDP 130 
#define  NF_TPROXY_LOOKUP_ESTABLISHED 129 
#define  NF_TPROXY_LOOKUP_LISTENER 128 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sock* __inet6_lookup_established (struct net*,int /*<<< orphan*/ *,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tcp_hdrlen (struct tcphdr*) ; 
 struct sock* inet6_lookup_listener (struct net*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pr_debug (char*,int const,struct in6_addr const*,int /*<<< orphan*/ ,struct in6_addr const*,int /*<<< orphan*/ ,int const,struct sock*) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct sock* udp6_lib_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

struct sock *
nf_tproxy_get_sock_v6(struct net *net, struct sk_buff *skb, int thoff,
		      const u8 protocol,
		      const struct in6_addr *saddr, const struct in6_addr *daddr,
		      const __be16 sport, const __be16 dport,
		      const struct net_device *in,
		      const enum nf_tproxy_lookup_t lookup_type)
{
	struct sock *sk;

	switch (protocol) {
	case IPPROTO_TCP: {
		struct tcphdr _hdr, *hp;

		hp = skb_header_pointer(skb, thoff,
					sizeof(struct tcphdr), &_hdr);
		if (hp == NULL)
			return NULL;

		switch (lookup_type) {
		case NF_TPROXY_LOOKUP_LISTENER:
			sk = inet6_lookup_listener(net, &tcp_hashinfo, skb,
						   thoff + __tcp_hdrlen(hp),
						   saddr, sport,
						   daddr, ntohs(dport),
						   in->ifindex, 0);

			if (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
				sk = NULL;
			/* NOTE: we return listeners even if bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			break;
		case NF_TPROXY_LOOKUP_ESTABLISHED:
			sk = __inet6_lookup_established(net, &tcp_hashinfo,
							saddr, sport, daddr, ntohs(dport),
							in->ifindex, 0);
			break;
		default:
			BUG();
		}
		break;
		}
	case IPPROTO_UDP:
		sk = udp6_lib_lookup(net, saddr, sport, daddr, dport,
				     in->ifindex);
		if (sk) {
			int connected = (sk->sk_state == TCP_ESTABLISHED);
			int wildcard = ipv6_addr_any(&sk->sk_v6_rcv_saddr);

			/* NOTE: we return listeners even if bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			if ((lookup_type == NF_TPROXY_LOOKUP_ESTABLISHED && (!connected || wildcard)) ||
			    (lookup_type == NF_TPROXY_LOOKUP_LISTENER && connected)) {
				sock_put(sk);
				sk = NULL;
			}
		}
		break;
	default:
		WARN_ON(1);
		sk = NULL;
	}

	pr_debug("tproxy socket lookup: proto %u %pI6:%u -> %pI6:%u, lookup type: %d, sock %p\n",
		 protocol, saddr, ntohs(sport), daddr, ntohs(dport), lookup_type, sk);

	return sk;
}