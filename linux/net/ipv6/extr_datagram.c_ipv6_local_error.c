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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ee_errno; scalar_t__ ee_data; int /*<<< orphan*/  ee_info; scalar_t__ ee_pad; scalar_t__ ee_code; scalar_t__ ee_type; int /*<<< orphan*/  ee_origin; } ;
struct sock_exterr_skb {int /*<<< orphan*/  port; int /*<<< orphan*/ * addr_offset; TYPE_1__ ee; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct ipv6_pinfo {int /*<<< orphan*/  recverr; } ;
struct flowi6 {int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_LOCAL ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ sock_queue_err_skb (struct sock*,struct sk_buff*) ; 

void ipv6_local_error(struct sock *sk, int err, struct flowi6 *fl6, u32 info)
{
	const struct ipv6_pinfo *np = inet6_sk(sk);
	struct sock_exterr_skb *serr;
	struct ipv6hdr *iph;
	struct sk_buff *skb;

	if (!np->recverr)
		return;

	skb = alloc_skb(sizeof(struct ipv6hdr), GFP_ATOMIC);
	if (!skb)
		return;

	skb->protocol = htons(ETH_P_IPV6);

	skb_put(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);
	iph->daddr = fl6->daddr;
	ip6_flow_hdr(iph, 0, 0);

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_errno = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_LOCAL;
	serr->ee.ee_type = 0;
	serr->ee.ee_code = 0;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&iph->daddr - skb_network_header(skb);
	serr->port = fl6->fl6_dport;

	__skb_pull(skb, skb_tail_pointer(skb) - skb->data);
	skb_reset_transport_header(skb);

	if (sock_queue_err_skb(sk, skb))
		kfree_skb(skb);
}