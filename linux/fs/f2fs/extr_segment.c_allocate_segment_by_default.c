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
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {scalar_t__ alloc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CRC_RECOVERY_FLAG ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int CURSEG_WARM_NODE ; 
 scalar_t__ LFS ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  change_curseg (struct f2fs_sb_info*,int) ; 
 scalar_t__ f2fs_need_SSR (struct f2fs_sb_info*) ; 
 scalar_t__ get_ssr_segment (struct f2fs_sb_info*,int) ; 
 scalar_t__ is_next_segment_free (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  new_curseg (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  stat_inc_seg_type (struct f2fs_sb_info*,struct curseg_info*) ; 

__attribute__((used)) static void allocate_segment_by_default(struct f2fs_sb_info *sbi,
						int type, bool force)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);

	if (force)
		new_curseg(sbi, type, true);
	else if (!is_set_ckpt_flags(sbi, CP_CRC_RECOVERY_FLAG) &&
					type == CURSEG_WARM_NODE)
		new_curseg(sbi, type, false);
	else if (curseg->alloc_type == LFS && is_next_segment_free(sbi, type) &&
			likely(!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		new_curseg(sbi, type, false);
	else if (f2fs_need_SSR(sbi) && get_ssr_segment(sbi, type))
		change_curseg(sbi, type);
	else
		new_curseg(sbi, type, false);

	stat_inc_seg_type(sbi, curseg);
}