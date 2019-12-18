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
struct xt_conntrack_mtinfo2 {int /*<<< orphan*/  status_mask; int /*<<< orphan*/  state_mask; } ;
struct xt_action_param {struct xt_conntrack_mtinfo2* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int conntrack_mt (struct sk_buff const*,struct xt_action_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
conntrack_mt_v2(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_conntrack_mtinfo2 *info = par->matchinfo;

	return conntrack_mt(skb, par, info->state_mask, info->status_mask);
}