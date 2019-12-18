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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct sctphdr {int /*<<< orphan*/  checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  sctp_compute_cksum (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void sctp_nat_csum(struct sk_buff *skb, struct sctphdr *sctph,
			  unsigned int sctphoff)
{
	sctph->checksum = sctp_compute_cksum(skb, sctphoff);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
}