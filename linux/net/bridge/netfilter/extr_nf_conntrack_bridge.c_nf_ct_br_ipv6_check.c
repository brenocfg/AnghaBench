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
struct sk_buff {int len; } ;
struct ipv6hdr {int version; int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int skb_network_offset (struct sk_buff const*) ; 

__attribute__((used)) static int nf_ct_br_ipv6_check(const struct sk_buff *skb)
{
	const struct ipv6hdr *hdr;
	int nhoff, len;

	nhoff = skb_network_offset(skb);
	hdr = ipv6_hdr(skb);
	if (hdr->version != 6)
		return -1;

	len = ntohs(hdr->payload_len) + sizeof(struct ipv6hdr) + nhoff;
	if (skb->len < len)
		return -1;

	return 0;
}