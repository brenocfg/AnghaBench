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
typedef  int u_int8_t ;
struct xt_tos_target_info {int tos_mask; int tos_value; } ;
struct xt_action_param {struct xt_tos_target_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  ipv6_change_dsfield (struct ipv6hdr*,int /*<<< orphan*/ ,int) ; 
 int ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int) ; 

__attribute__((used)) static unsigned int
tos_tg6(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_tos_target_info *info = par->targinfo;
	struct ipv6hdr *iph = ipv6_hdr(skb);
	u_int8_t orig, nv;

	orig = ipv6_get_dsfield(iph);
	nv   = (orig & ~info->tos_mask) ^ info->tos_value;

	if (orig != nv) {
		if (skb_ensure_writable(skb, sizeof(struct iphdr)))
			return NF_DROP;
		iph = ipv6_hdr(skb);
		ipv6_change_dsfield(iph, 0, nv);
	}

	return XT_CONTINUE;
}