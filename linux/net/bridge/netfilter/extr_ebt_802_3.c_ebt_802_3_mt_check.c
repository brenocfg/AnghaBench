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
struct xt_mtchk_param {struct ebt_802_3_info* matchinfo; } ;
struct ebt_802_3_info {int bitmask; int invflags; } ;

/* Variables and functions */
 int EBT_802_3_MASK ; 
 int EINVAL ; 

__attribute__((used)) static int ebt_802_3_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_802_3_info *info = par->matchinfo;

	if (info->bitmask & ~EBT_802_3_MASK || info->invflags & ~EBT_802_3_MASK)
		return -EINVAL;

	return 0;
}