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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; } ;
struct net {int dummy; } ;
struct iphdr {int version; int ihl; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  protocol; void* saddr; void* daddr; scalar_t__ frag_off; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
typedef  void* __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_select_ident (struct net*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void ip_encap(struct net *net, struct sk_buff *skb,
		     __be32 saddr, __be32 daddr)
{
	struct iphdr *iph;
	const struct iphdr *old_iph = ip_hdr(skb);

	skb_push(skb, sizeof(struct iphdr));
	skb->transport_header = skb->network_header;
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);

	iph->version	=	4;
	iph->tos	=	old_iph->tos;
	iph->ttl	=	old_iph->ttl;
	iph->frag_off	=	0;
	iph->daddr	=	daddr;
	iph->saddr	=	saddr;
	iph->protocol	=	IPPROTO_IPIP;
	iph->ihl	=	5;
	iph->tot_len	=	htons(skb->len);
	ip_select_ident(net, skb, NULL);
	ip_send_check(iph);

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	nf_reset_ct(skb);
}