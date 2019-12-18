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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ipv6_rt_hdr {int type; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  IPV6_SRCRT_STRICT 131 
#define  IPV6_SRCRT_TYPE_0 130 
#define  IPV6_SRCRT_TYPE_2 129 
#define  IPV6_SRCRT_TYPE_4 128 
 int /*<<< orphan*/  ipv6_push_rthdr0 (struct sk_buff*,int /*<<< orphan*/ *,struct ipv6_rt_hdr*,struct in6_addr**,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_push_rthdr4 (struct sk_buff*,int /*<<< orphan*/ *,struct ipv6_rt_hdr*,struct in6_addr**,struct in6_addr*) ; 

__attribute__((used)) static void ipv6_push_rthdr(struct sk_buff *skb, u8 *proto,
			    struct ipv6_rt_hdr *opt,
			    struct in6_addr **addr_p, struct in6_addr *saddr)
{
	switch (opt->type) {
	case IPV6_SRCRT_TYPE_0:
	case IPV6_SRCRT_STRICT:
	case IPV6_SRCRT_TYPE_2:
		ipv6_push_rthdr0(skb, proto, opt, addr_p, saddr);
		break;
	case IPV6_SRCRT_TYPE_4:
		ipv6_push_rthdr4(skb, proto, opt, addr_p, saddr);
		break;
	default:
		break;
	}
}