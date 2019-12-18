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
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  flowi4_scope; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_iif; } ;
typedef  int /*<<< orphan*/  flow ;

/* Variables and functions */
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int XT_RPFILTER_INVERT ; 
 int XT_RPFILTER_VALID_MARK ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ ipv4_is_lbcast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3mdev_master_ifindex_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpfilter_get_saddr (int /*<<< orphan*/ ) ; 
 scalar_t__ rpfilter_is_loopback (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int rpfilter_lookup_reverse (int /*<<< orphan*/ ,struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool rpfilter_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_rpfilter_info *info;
	const struct iphdr *iph;
	struct flowi4 flow;
	bool invert;

	info = par->matchinfo;
	invert = info->flags & XT_RPFILTER_INVERT;

	if (rpfilter_is_loopback(skb, xt_in(par)))
		return true ^ invert;

	iph = ip_hdr(skb);
	if (ipv4_is_zeronet(iph->saddr)) {
		if (ipv4_is_lbcast(iph->daddr) ||
		    ipv4_is_local_multicast(iph->daddr))
			return true ^ invert;
	}

	memset(&flow, 0, sizeof(flow));
	flow.flowi4_iif = LOOPBACK_IFINDEX;
	flow.daddr = iph->saddr;
	flow.saddr = rpfilter_get_saddr(iph->daddr);
	flow.flowi4_mark = info->flags & XT_RPFILTER_VALID_MARK ? skb->mark : 0;
	flow.flowi4_tos = RT_TOS(iph->tos);
	flow.flowi4_scope = RT_SCOPE_UNIVERSE;
	flow.flowi4_oif = l3mdev_master_ifindex_rcu(xt_in(par));

	return rpfilter_lookup_reverse(xt_net(par), &flow, xt_in(par), info->flags) ^ invert;
}