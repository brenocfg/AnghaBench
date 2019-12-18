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
struct super_block {int /*<<< orphan*/  s_flags; scalar_t__ s_root; } ;
struct f2fs_sb_info {int dummy; } ;
struct cp_control {int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UMOUNT ; 
 int /*<<< orphan*/  CP_UMOUNT_FLAG ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SBI_IS_CLOSE ; 
 int /*<<< orphan*/  SBI_IS_DIRTY ; 
 int /*<<< orphan*/  SBI_IS_RECOVERED ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 scalar_t__ f2fs_readonly (struct super_block*) ; 
 int /*<<< orphan*/  f2fs_stop_discard_thread (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_stop_gc_thread (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_write_checkpoint (struct f2fs_sb_info*,struct cp_control*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_f2fs_super(struct super_block *sb)
{
	if (sb->s_root) {
		struct f2fs_sb_info *sbi = F2FS_SB(sb);

		set_sbi_flag(sbi, SBI_IS_CLOSE);
		f2fs_stop_gc_thread(sbi);
		f2fs_stop_discard_thread(sbi);

		if (is_sbi_flag_set(sbi, SBI_IS_DIRTY) ||
				!is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG)) {
			struct cp_control cpc = {
				.reason = CP_UMOUNT,
			};
			f2fs_write_checkpoint(sbi, &cpc);
		}

		if (is_sbi_flag_set(sbi, SBI_IS_RECOVERED) && f2fs_readonly(sb))
			sb->s_flags &= ~SB_RDONLY;
	}
	kill_block_super(sb);
}