#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int doff; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {int /*<<< orphan*/  sk_rx_dst; } ;
struct sk_buff {scalar_t__ pkt_type; scalar_t__ skb_iif; int /*<<< orphan*/  destructor; struct sock* sk; int /*<<< orphan*/  dev; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_dst_cookie; } ;
struct TYPE_3__ {scalar_t__ rx_dst_ifindex; } ;

/* Variables and functions */
 scalar_t__ PACKET_HOST ; 
 struct dst_entry* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct sock* __inet6_lookup_established (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct dst_entry* dst_check (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  inet6_sdif (struct sk_buff*) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_edemux ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void tcp_v6_early_demux(struct sk_buff *skb)
{
	const struct ipv6hdr *hdr;
	const struct tcphdr *th;
	struct sock *sk;

	if (skb->pkt_type != PACKET_HOST)
		return;

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + sizeof(struct tcphdr)))
		return;

	hdr = ipv6_hdr(skb);
	th = tcp_hdr(skb);

	if (th->doff < sizeof(struct tcphdr) / 4)
		return;

	/* Note : We use inet6_iif() here, not tcp_v6_iif() */
	sk = __inet6_lookup_established(dev_net(skb->dev), &tcp_hashinfo,
					&hdr->saddr, th->source,
					&hdr->daddr, ntohs(th->dest),
					inet6_iif(skb), inet6_sdif(skb));
	if (sk) {
		skb->sk = sk;
		skb->destructor = sock_edemux;
		if (sk_fullsock(sk)) {
			struct dst_entry *dst = READ_ONCE(sk->sk_rx_dst);

			if (dst)
				dst = dst_check(dst, inet6_sk(sk)->rx_dst_cookie);
			if (dst &&
			    inet_sk(sk)->rx_dst_ifindex == skb->skb_iif)
				skb_dst_set_noref(skb, dst);
		}
	}
}