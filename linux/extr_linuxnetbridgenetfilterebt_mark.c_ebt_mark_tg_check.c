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
struct xt_tgchk_param {struct ebt_mark_t_info* targinfo; } ;
struct ebt_mark_t_info {int target; } ;

/* Variables and functions */
 scalar_t__ BASE_CHAIN ; 
 int EBT_RETURN ; 
 int EBT_VERDICT_BITS ; 
 int EINVAL ; 
 int MARK_AND_VALUE ; 
 int MARK_OR_VALUE ; 
 int MARK_SET_VALUE ; 
 int MARK_XOR_VALUE ; 
 scalar_t__ ebt_invalid_target (int) ; 

__attribute__((used)) static int ebt_mark_tg_check(const struct xt_tgchk_param *par)
{
	const struct ebt_mark_t_info *info = par->targinfo;
	int tmp;

	tmp = info->target | ~EBT_VERDICT_BITS;
	if (BASE_CHAIN && tmp == EBT_RETURN)
		return -EINVAL;
	if (ebt_invalid_target(tmp))
		return -EINVAL;
	tmp = info->target & ~EBT_VERDICT_BITS;
	if (tmp != MARK_SET_VALUE && tmp != MARK_OR_VALUE &&
	    tmp != MARK_AND_VALUE && tmp != MARK_XOR_VALUE)
		return -EINVAL;
	return 0;
}