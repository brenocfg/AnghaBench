#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xt_devgroup_info {int flags; int src_group; int src_mask; int dst_group; int dst_mask; } ;
struct xt_action_param {struct xt_devgroup_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int group; } ;
struct TYPE_3__ {int group; } ;

/* Variables and functions */
 int XT_DEVGROUP_INVERT_DST ; 
 int XT_DEVGROUP_INVERT_SRC ; 
 int XT_DEVGROUP_MATCH_DST ; 
 int XT_DEVGROUP_MATCH_SRC ; 
 TYPE_2__* xt_in (struct xt_action_param*) ; 
 TYPE_1__* xt_out (struct xt_action_param*) ; 

__attribute__((used)) static bool devgroup_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_devgroup_info *info = par->matchinfo;

	if (info->flags & XT_DEVGROUP_MATCH_SRC &&
	    (((info->src_group ^ xt_in(par)->group) & info->src_mask ? 1 : 0) ^
	     ((info->flags & XT_DEVGROUP_INVERT_SRC) ? 1 : 0)))
		return false;

	if (info->flags & XT_DEVGROUP_MATCH_DST &&
	    (((info->dst_group ^ xt_out(par)->group) & info->dst_mask ? 1 : 0) ^
	     ((info->flags & XT_DEVGROUP_INVERT_DST) ? 1 : 0)))
		return false;

	return true;
}