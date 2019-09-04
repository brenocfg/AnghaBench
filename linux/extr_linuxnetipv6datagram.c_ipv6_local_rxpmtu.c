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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxpmtu; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct ipv6_pinfo {int /*<<< orphan*/  rxpmtu; TYPE_2__ rxopt; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; scalar_t__ sin6_flowinfo; scalar_t__ sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct ip6_mtuinfo {TYPE_3__ ip6m_addr; int /*<<< orphan*/  ip6m_mtu; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ip6_mtuinfo* IP6CBMTU (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,struct sk_buff*) ; 

void ipv6_local_rxpmtu(struct sock *sk, struct flowi6 *fl6, u32 mtu)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6hdr *iph;
	struct sk_buff *skb;
	struct ip6_mtuinfo *mtu_info;

	if (!np->rxopt.bits.rxpmtu)
		return;

	skb = alloc_skb(sizeof(struct ipv6hdr), GFP_ATOMIC);
	if (!skb)
		return;

	skb_put(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);
	iph->daddr = fl6->daddr;

	mtu_info = IP6CBMTU(skb);

	mtu_info->ip6m_mtu = mtu;
	mtu_info->ip6m_addr.sin6_family = AF_INET6;
	mtu_info->ip6m_addr.sin6_port = 0;
	mtu_info->ip6m_addr.sin6_flowinfo = 0;
	mtu_info->ip6m_addr.sin6_scope_id = fl6->flowi6_oif;
	mtu_info->ip6m_addr.sin6_addr = ipv6_hdr(skb)->daddr;

	__skb_pull(skb, skb_tail_pointer(skb) - skb->data);
	skb_reset_transport_header(skb);

	skb = xchg(&np->rxpmtu, skb);
	kfree_skb(skb);
}