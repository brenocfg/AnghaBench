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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  diff ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  csum_partial (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skb_mod_eth_type(struct sk_buff *skb, struct ethhdr *hdr,
			     __be16 ethertype)
{
	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		__be16 diff[] = { ~hdr->h_proto, ethertype };

		skb->csum = csum_partial((char *)diff, sizeof(diff), skb->csum);
	}

	hdr->h_proto = ethertype;
}