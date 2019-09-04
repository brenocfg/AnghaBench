#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  index; int /*<<< orphan*/  dim; } ;
struct xt_set_info_match_v1 {TYPE_1__ match_set; } ;
struct xt_action_param {struct xt_set_info_match_v1* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  cmdflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT_OPT (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSET_FLAG_RETURN_NOMATCH ; 
 int IPSET_INV_MATCH ; 
 int IPSET_RETURN_NOMATCH ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int match_set (int /*<<< orphan*/ ,struct sk_buff const*,struct xt_action_param*,TYPE_2__*,int) ; 
 TYPE_2__ opt ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param*) ; 

__attribute__((used)) static bool
set_match_v1(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_set_info_match_v1 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.dim,
		info->match_set.flags, 0, UINT_MAX,
		0, 0, 0, 0);

	if (opt.flags & IPSET_RETURN_NOMATCH)
		opt.cmdflags |= IPSET_FLAG_RETURN_NOMATCH;

	return match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.flags & IPSET_INV_MATCH);
}