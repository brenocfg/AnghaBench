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
struct xt_action_param {struct ip6t_hl_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  hop_limit; } ;
struct ip6t_hl_info {int mode; int /*<<< orphan*/  hop_limit; } ;

/* Variables and functions */
#define  IP6T_HL_EQ 131 
#define  IP6T_HL_GT 130 
#define  IP6T_HL_LT 129 
#define  IP6T_HL_NE 128 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static bool hl_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ip6t_hl_info *info = par->matchinfo;
	const struct ipv6hdr *ip6h = ipv6_hdr(skb);

	switch (info->mode) {
	case IP6T_HL_EQ:
		return ip6h->hop_limit == info->hop_limit;
	case IP6T_HL_NE:
		return ip6h->hop_limit != info->hop_limit;
	case IP6T_HL_LT:
		return ip6h->hop_limit < info->hop_limit;
	case IP6T_HL_GT:
		return ip6h->hop_limit > info->hop_limit;
	}

	return false;
}