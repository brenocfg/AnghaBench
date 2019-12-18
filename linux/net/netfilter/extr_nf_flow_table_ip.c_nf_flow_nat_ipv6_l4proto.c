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
struct sk_buff {int dummy; } ;
struct ipv6hdr {int nexthdr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int NF_DROP ; 
 int /*<<< orphan*/  nf_flow_nat_ipv6_tcp (struct sk_buff*,unsigned int,struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  nf_flow_nat_ipv6_udp (struct sk_buff*,unsigned int,struct in6_addr*,struct in6_addr*) ; 

__attribute__((used)) static int nf_flow_nat_ipv6_l4proto(struct sk_buff *skb, struct ipv6hdr *ip6h,
				    unsigned int thoff, struct in6_addr *addr,
				    struct in6_addr *new_addr)
{
	switch (ip6h->nexthdr) {
	case IPPROTO_TCP:
		if (nf_flow_nat_ipv6_tcp(skb, thoff, addr, new_addr) < 0)
			return NF_DROP;
		break;
	case IPPROTO_UDP:
		if (nf_flow_nat_ipv6_udp(skb, thoff, addr, new_addr) < 0)
			return NF_DROP;
		break;
	}

	return 0;
}