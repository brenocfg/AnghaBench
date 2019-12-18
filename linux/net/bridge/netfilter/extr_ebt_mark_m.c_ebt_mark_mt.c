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
struct xt_action_param {struct ebt_mark_m_info* matchinfo; } ;
struct sk_buff {int mark; } ;
struct ebt_mark_m_info {int bitmask; int mask; int invert; int mark; } ;

/* Variables and functions */
 int EBT_MARK_OR ; 

__attribute__((used)) static bool
ebt_mark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ebt_mark_m_info *info = par->matchinfo;

	if (info->bitmask & EBT_MARK_OR)
		return !!(skb->mark & info->mask) ^ info->invert;
	return ((skb->mark & info->mask) == info->mark) ^ info->invert;
}