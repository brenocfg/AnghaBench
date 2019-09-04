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
struct tcphdr {scalar_t__ const dest; int /*<<< orphan*/  source; int /*<<< orphan*/  fin; int /*<<< orphan*/  ack; int /*<<< orphan*/  rst; scalar_t__ syn; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  _hdr ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  NF_TPROXY_LOOKUP_LISTENER ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_deschedule_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct sock* nf_tproxy_get_sock_v6 (struct net*,struct sk_buff*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tproxy_laddr6 (struct sk_buff*,struct in6_addr const*,int /*<<< orphan*/ *) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,int,int,struct tcphdr*) ; 

struct sock *
nf_tproxy_handle_time_wait6(struct sk_buff *skb, int tproto, int thoff,
			 struct net *net,
			 const struct in6_addr *laddr,
			 const __be16 lport,
			 struct sock *sk)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	struct tcphdr _hdr, *hp;

	hp = skb_header_pointer(skb, thoff, sizeof(_hdr), &_hdr);
	if (hp == NULL) {
		inet_twsk_put(inet_twsk(sk));
		return NULL;
	}

	if (hp->syn && !hp->rst && !hp->ack && !hp->fin) {
		/* SYN to a TIME_WAIT socket, we'd rather redirect it
		 * to a listener socket if there's one */
		struct sock *sk2;

		sk2 = nf_tproxy_get_sock_v6(net, skb, thoff, tproto,
					    &iph->saddr,
					    nf_tproxy_laddr6(skb, laddr, &iph->daddr),
					    hp->source,
					    lport ? lport : hp->dest,
					    skb->dev, NF_TPROXY_LOOKUP_LISTENER);
		if (sk2) {
			inet_twsk_deschedule_put(inet_twsk(sk));
			sk = sk2;
		}
	}

	return sk;
}