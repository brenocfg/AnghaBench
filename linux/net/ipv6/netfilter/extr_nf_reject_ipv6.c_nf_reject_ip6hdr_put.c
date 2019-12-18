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
typedef  struct sk_buff {int /*<<< orphan*/  protocol; } const sk_buff ;
struct ipv6hdr {int hop_limit; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  nexthdr; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TOS_VALUE ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 void* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff const*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff const*) ; 

struct ipv6hdr *nf_reject_ip6hdr_put(struct sk_buff *nskb,
				     const struct sk_buff *oldskb,
				     __u8 protocol, int hoplimit)
{
	struct ipv6hdr *ip6h;
	const struct ipv6hdr *oip6h = ipv6_hdr(oldskb);
#define DEFAULT_TOS_VALUE	0x0U
	const __u8 tclass = DEFAULT_TOS_VALUE;

	skb_put(nskb, sizeof(struct ipv6hdr));
	skb_reset_network_header(nskb);
	ip6h = ipv6_hdr(nskb);
	ip6_flow_hdr(ip6h, tclass, 0);
	ip6h->hop_limit = hoplimit;
	ip6h->nexthdr = protocol;
	ip6h->saddr = oip6h->daddr;
	ip6h->daddr = oip6h->saddr;

	nskb->protocol = htons(ETH_P_IPV6);

	return ip6h;
}