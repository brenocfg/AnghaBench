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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct icmp6hdr {scalar_t__ icmp6_cksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct icmp6hdr*,unsigned int,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct icmp6hdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_ipv6_icmp(struct sk_buff *skb, unsigned int ihl,
			      unsigned int ipl)
{
	struct icmp6hdr *icmp6h;
	const struct ipv6hdr *ip6h;

	icmp6h = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*icmp6h));
	if (icmp6h == NULL)
		return 0;

	ip6h = ipv6_hdr(skb);
	icmp6h->icmp6_cksum = 0;
	skb->csum = csum_partial(icmp6h, ipl - ihl, 0);
	icmp6h->icmp6_cksum = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					      ipl - ihl, IPPROTO_ICMPV6,
					      skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	return 1;
}