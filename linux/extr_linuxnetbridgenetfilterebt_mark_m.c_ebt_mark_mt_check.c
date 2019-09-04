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
struct xt_mtchk_param {struct ebt_mark_m_info* matchinfo; } ;
struct ebt_mark_m_info {int bitmask; } ;

/* Variables and functions */
 int EBT_MARK_AND ; 
 int EBT_MARK_MASK ; 
 int EBT_MARK_OR ; 
 int EINVAL ; 

__attribute__((used)) static int ebt_mark_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_mark_m_info *info = par->matchinfo;

	if (info->bitmask & ~EBT_MARK_MASK)
		return -EINVAL;
	if ((info->bitmask & EBT_MARK_OR) && (info->bitmask & EBT_MARK_AND))
		return -EINVAL;
	if (!info->bitmask)
		return -EINVAL;
	return 0;
}