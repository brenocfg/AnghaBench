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
struct f2fs_sb_info {unsigned int cur_victim_sec; } ;

/* Variables and functions */
 scalar_t__ IS_CURSEC (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static inline bool sec_usage_check(struct f2fs_sb_info *sbi, unsigned int secno)
{
	if (IS_CURSEC(sbi, secno) || (sbi->cur_victim_sec == secno))
		return true;
	return false;
}