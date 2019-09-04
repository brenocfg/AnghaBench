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
struct xt_tgchk_param {struct ebt_nflog_info* targinfo; } ;
struct ebt_nflog_info {int flags; char* prefix; } ;

/* Variables and functions */
 int EBT_NFLOG_MASK ; 
 int EBT_NFLOG_PREFIX_SIZE ; 
 int EINVAL ; 

__attribute__((used)) static int ebt_nflog_tg_check(const struct xt_tgchk_param *par)
{
	struct ebt_nflog_info *info = par->targinfo;

	if (info->flags & ~EBT_NFLOG_MASK)
		return -EINVAL;
	info->prefix[EBT_NFLOG_PREFIX_SIZE - 1] = '\0';
	return 0;
}