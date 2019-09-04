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
struct xt_ecn_info {int operation; } ;
struct xt_action_param {struct xt_ecn_info* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int XT_ECN_OP_MATCH_CWR ; 
 int XT_ECN_OP_MATCH_ECE ; 
 int XT_ECN_OP_MATCH_IP ; 
 int /*<<< orphan*/  match_ipv6 (struct sk_buff const*,struct xt_ecn_info const*) ; 
 int /*<<< orphan*/  match_tcp (struct sk_buff const*,struct xt_action_param*) ; 

__attribute__((used)) static bool ecn_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_ecn_info *info = par->matchinfo;

	if (info->operation & XT_ECN_OP_MATCH_IP && !match_ipv6(skb, info))
		return false;

	if (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    !match_tcp(skb, par))
		return false;

	return true;
}