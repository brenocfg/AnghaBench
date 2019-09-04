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
struct udphdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct sock {int /*<<< orphan*/  sk_rx_dst; int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  destructor; struct sock* sk; TYPE_3__* dev; } ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {int ifindex; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_dst_cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ PACKET_HOST ; 
 struct dst_entry* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct sock* __udp6_lib_demux_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 struct net* dev_net (TYPE_3__*) ; 
 struct dst_entry* dst_check (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int inet6_sdif (struct sk_buff*) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_efree ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void udp_v6_early_demux(struct sk_buff *skb)
{
	struct net *net = dev_net(skb->dev);
	const struct udphdr *uh;
	struct sock *sk;
	struct dst_entry *dst;
	int dif = skb->dev->ifindex;
	int sdif = inet6_sdif(skb);

	if (!pskb_may_pull(skb, skb_transport_offset(skb) +
	    sizeof(struct udphdr)))
		return;

	uh = udp_hdr(skb);

	if (skb->pkt_type == PACKET_HOST)
		sk = __udp6_lib_demux_lookup(net, uh->dest,
					     &ipv6_hdr(skb)->daddr,
					     uh->source, &ipv6_hdr(skb)->saddr,
					     dif, sdif);
	else
		return;

	if (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		return;

	skb->sk = sk;
	skb->destructor = sock_efree;
	dst = READ_ONCE(sk->sk_rx_dst);

	if (dst)
		dst = dst_check(dst, inet6_sk(sk)->rx_dst_cookie);
	if (dst) {
		/* set noref for now.
		 * any place which wants to hold dst has to call
		 * dst_hold_safe()
		 */
		skb_dst_set_noref(skb, dst);
	}
}