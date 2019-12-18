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
struct super_block {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  gc_mutex; } ;
struct cp_control {int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 int /*<<< orphan*/  __get_cp_reason (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_trace_ios (int /*<<< orphan*/ *,int) ; 
 int f2fs_write_checkpoint (struct f2fs_sb_info*,struct cp_control*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_sync_fs (struct super_block*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int f2fs_sync_fs(struct super_block *sb, int sync)
{
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	int err = 0;

	if (unlikely(f2fs_cp_error(sbi)))
		return 0;
	if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		return 0;

	trace_f2fs_sync_fs(sb, sync);

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		return -EAGAIN;

	if (sync) {
		struct cp_control cpc;

		cpc.reason = __get_cp_reason(sbi);

		mutex_lock(&sbi->gc_mutex);
		err = f2fs_write_checkpoint(sbi, &cpc);
		mutex_unlock(&sbi->gc_mutex);
	}
	f2fs_trace_ios(NULL, 1);

	return err;
}