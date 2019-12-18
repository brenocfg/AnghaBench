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
struct tcphdr {scalar_t__ check; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int SKB_GSO_TCPV6 ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct tcphdr*,unsigned int,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct tcphdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_ipv6_tcp(struct sk_buff *skb, unsigned int ihl,
			     unsigned int ipl)
{
	struct tcphdr *tcph;
	const struct ipv6hdr *ip6h;

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
		return 1;

	tcph = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*tcph));
	if (tcph == NULL)
		return 0;

	ip6h = ipv6_hdr(skb);
	tcph->check = 0;
	skb->csum = csum_partial(tcph, ipl - ihl, 0);
	tcph->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
				      ipl - ihl, IPPROTO_TCP,
				      skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	return 1;
}