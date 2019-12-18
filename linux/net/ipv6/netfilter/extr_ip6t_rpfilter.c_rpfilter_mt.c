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
struct xt_rpfilter_info {int flags; } ;
struct xt_action_param {struct xt_rpfilter_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int IPV6_ADDR_ANY ; 
 int XT_RPFILTER_INVERT ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 
 scalar_t__ rpfilter_is_loopback (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int rpfilter_lookup_reverse6 (int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool rpfilter_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_rpfilter_info *info = par->matchinfo;
	int saddrtype;
	struct ipv6hdr *iph;
	bool invert = info->flags & XT_RPFILTER_INVERT;

	if (rpfilter_is_loopback(skb, xt_in(par)))
		return true ^ invert;

	iph = ipv6_hdr(skb);
	saddrtype = ipv6_addr_type(&iph->saddr);
	if (unlikely(saddrtype == IPV6_ADDR_ANY))
		return true ^ invert; /* not routable: forward path will drop it */

	return rpfilter_lookup_reverse6(xt_net(par), skb, xt_in(par),
					info->flags) ^ invert;
}