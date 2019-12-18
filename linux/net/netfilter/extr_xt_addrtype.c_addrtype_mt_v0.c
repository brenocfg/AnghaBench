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
struct xt_addrtype_info {int invert_source; int invert_dest; scalar_t__ dest; scalar_t__ source; } ;
struct xt_action_param {struct xt_addrtype_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int match_type (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct net* xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool
addrtype_mt_v0(const struct sk_buff *skb, struct xt_action_param *par)
{
	struct net *net = xt_net(par);
	const struct xt_addrtype_info *info = par->matchinfo;
	const struct iphdr *iph = ip_hdr(skb);
	bool ret = true;

	if (info->source)
		ret &= match_type(net, NULL, iph->saddr, info->source) ^
		       info->invert_source;
	if (info->dest)
		ret &= match_type(net, NULL, iph->daddr, info->dest) ^
		       info->invert_dest;

	return ret;
}