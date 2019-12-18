#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int dummy; } ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {scalar_t__ unusable_cap; } ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SBI_CP_DISABLED_QUICK ; 
 int dirty_segments (struct f2fs_sb_info*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int overprovision_segments (struct f2fs_sb_info*) ; 
 int reserved_segments (struct f2fs_sb_info*) ; 

int f2fs_disable_cp_again(struct f2fs_sb_info *sbi, block_t unusable)
{
	int ovp_hole_segs =
		(overprovision_segments(sbi) - reserved_segments(sbi));
	if (unusable > F2FS_OPTION(sbi).unusable_cap)
		return -EAGAIN;
	if (is_sbi_flag_set(sbi, SBI_CP_DISABLED_QUICK) &&
		dirty_segments(sbi) > ovp_hole_segs)
		return -EAGAIN;
	return 0;
}