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
struct sk_buff {scalar_t__ csum_not_inet; int /*<<< orphan*/  ip_summed; } ;
struct sctphdr {int /*<<< orphan*/  checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  sctp_compute_cksum (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_sctp (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 struct sctphdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_sctp(struct sk_buff *skb, unsigned int ihl,
			 unsigned int ipl)
{
	struct sctphdr *sctph;

	if (skb_is_gso(skb) && skb_is_gso_sctp(skb))
		return 1;

	sctph = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*sctph));
	if (!sctph)
		return 0;

	sctph->checksum = sctp_compute_cksum(skb,
					     skb_network_offset(skb) + ihl);
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_not_inet = 0;

	return 1;
}