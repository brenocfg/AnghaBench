#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  index; int /*<<< orphan*/  dim; } ;
struct TYPE_8__ {scalar_t__ op; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {scalar_t__ op; int /*<<< orphan*/  value; } ;
struct xt_set_info_match_v4 {TYPE_3__ match_set; TYPE_2__ bytes; TYPE_1__ packets; int /*<<< orphan*/  flags; } ;
struct xt_action_param {struct xt_set_info_match_v4* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  cmdflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT_OPT (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ IPSET_COUNTER_NONE ; 
 int /*<<< orphan*/  IPSET_FLAG_MATCH_COUNTERS ; 
 int IPSET_INV_MATCH ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int match_set (int /*<<< orphan*/ ,struct sk_buff const*,struct xt_action_param*,TYPE_4__*,int) ; 
 TYPE_4__ opt ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param*) ; 

__attribute__((used)) static bool
set_match_v4(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_set_info_match_v4 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.dim,
		info->match_set.flags, info->flags, UINT_MAX,
		info->packets.value, info->bytes.value,
		info->packets.op, info->bytes.op);

	if (info->packets.op != IPSET_COUNTER_NONE ||
	    info->bytes.op != IPSET_COUNTER_NONE)
		opt.cmdflags |= IPSET_FLAG_MATCH_COUNTERS;

	return match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.flags & IPSET_INV_MATCH);
}