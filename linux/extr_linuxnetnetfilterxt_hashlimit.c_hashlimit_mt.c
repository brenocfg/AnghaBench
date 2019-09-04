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
struct xt_hashlimit_mtinfo3 {int /*<<< orphan*/  cfg; struct xt_hashlimit_htable* hinfo; } ;
struct xt_hashlimit_htable {int dummy; } ;
struct xt_action_param {struct xt_hashlimit_mtinfo3* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int hashlimit_mt_common (struct sk_buff const*,struct xt_action_param*,struct xt_hashlimit_htable*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
hashlimit_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_hashlimit_mtinfo3 *info = par->matchinfo;
	struct xt_hashlimit_htable *hinfo = info->hinfo;

	return hashlimit_mt_common(skb, par, hinfo, &info->cfg, 3);
}