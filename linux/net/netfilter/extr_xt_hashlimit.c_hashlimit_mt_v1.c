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
struct xt_hashlimit_mtinfo1 {int /*<<< orphan*/  cfg; struct xt_hashlimit_htable* hinfo; } ;
struct xt_hashlimit_htable {int dummy; } ;
struct xt_action_param {struct xt_hashlimit_mtinfo1* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct hashlimit_cfg3 {int dummy; } ;

/* Variables and functions */
 int cfg_copy (struct hashlimit_cfg3*,void*,int) ; 
 int hashlimit_mt_common (struct sk_buff const*,struct xt_action_param*,struct xt_hashlimit_htable*,struct hashlimit_cfg3*,int) ; 

__attribute__((used)) static bool
hashlimit_mt_v1(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_hashlimit_mtinfo1 *info = par->matchinfo;
	struct xt_hashlimit_htable *hinfo = info->hinfo;
	struct hashlimit_cfg3 cfg = {};
	int ret;

	ret = cfg_copy(&cfg, (void *)&info->cfg, 1);
	if (ret)
		return ret;

	return hashlimit_mt_common(skb, par, hinfo, &cfg, 1);
}