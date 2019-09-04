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
typedef  int u8 ;
struct tcphdr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
typedef  enum nf_tproxy_lookup_t { ____Placeholder_nf_tproxy_lookup_t } nf_tproxy_lookup_t ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  inet_rcv_saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  IPPROTO_TCP 131 
#define  IPPROTO_UDP 130 
#define  NF_TPROXY_LOOKUP_ESTABLISHED 129 
#define  NF_TPROXY_LOOKUP_LISTENER 128 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __tcp_hdrlen (struct tcphdr*) ; 
 struct sock* inet_lookup_established (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 struct sock* inet_lookup_listener (struct net*,int /*<<< orphan*/ *,struct sk_buff*,scalar_t__,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 scalar_t__ ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pr_debug (char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,struct sock*) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,scalar_t__,int,struct tcphdr*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct sock* udp4_lib_lookup (struct net*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

struct sock *
nf_tproxy_get_sock_v4(struct net *net, struct sk_buff *skb,
		      const u8 protocol,
		      const __be32 saddr, const __be32 daddr,
		      const __be16 sport, const __be16 dport,
		      const struct net_device *in,
		      const enum nf_tproxy_lookup_t lookup_type)
{
	struct sock *sk;

	switch (protocol) {
	case IPPROTO_TCP: {
		struct tcphdr _hdr, *hp;

		hp = skb_header_pointer(skb, ip_hdrlen(skb),
					sizeof(struct tcphdr), &_hdr);
		if (hp == NULL)
			return NULL;

		switch (lookup_type) {
		case NF_TPROXY_LOOKUP_LISTENER:
			sk = inet_lookup_listener(net, &tcp_hashinfo, skb,
						    ip_hdrlen(skb) +
						      __tcp_hdrlen(hp),
						    saddr, sport,
						    daddr, dport,
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
			sk = inet_lookup_established(net, &tcp_hashinfo,
						    saddr, sport, daddr, dport,
						    in->ifindex);
			break;
		default:
			BUG();
		}
		break;
		}
	case IPPROTO_UDP:
		sk = udp4_lib_lookup(net, saddr, sport, daddr, dport,
				     in->ifindex);
		if (sk) {
			int connected = (sk->sk_state == TCP_ESTABLISHED);
			int wildcard = (inet_sk(sk)->inet_rcv_saddr == 0);

			/* NOTE: we return listeners even if bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			if ((lookup_type == NF_TPROXY_LOOKUP_ESTABLISHED &&
			      (!connected || wildcard)) ||
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

	pr_debug("tproxy socket lookup: proto %u %08x:%u -> %08x:%u, lookup type: %d, sock %p\n",
		 protocol, ntohl(saddr), ntohs(sport), ntohl(daddr), ntohs(dport), lookup_type, sk);

	return sk;
}