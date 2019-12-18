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
struct icmphdr {scalar_t__ checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct icmphdr*,unsigned int,int /*<<< orphan*/ ) ; 
 struct icmphdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_ipv4_icmp(struct sk_buff *skb, unsigned int ihl,
			      unsigned int ipl)
{
	struct icmphdr *icmph;

	icmph = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*icmph));
	if (icmph == NULL)
		return 0;

	icmph->checksum = 0;
	skb->csum = csum_partial(icmph, ipl - ihl, 0);
	icmph->checksum = csum_fold(skb->csum);

	skb->ip_summed = CHECKSUM_NONE;

	return 1;
}