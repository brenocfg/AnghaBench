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
struct f2fs_sb_info {TYPE_1__* sb; int /*<<< orphan*/  gc_mutex; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  unusable_block_count; } ;
struct cp_control {int /*<<< orphan*/  reason; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_2__ {unsigned int s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PAUSE ; 
 int /*<<< orphan*/  DISABLE_TIME ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  NULL_SEGNO ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 unsigned int SB_ACTIVE ; 
 unsigned int SB_RDONLY ; 
 scalar_t__ f2fs_disable_cp_again (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*) ; 
 int f2fs_gc (struct f2fs_sb_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_get_unusable_blocks (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_time_over (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_write_checkpoint (struct f2fs_sb_info*,struct cp_control*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sync_filesystem (TYPE_1__*) ; 

__attribute__((used)) static int f2fs_disable_checkpoint(struct f2fs_sb_info *sbi)
{
	unsigned int s_flags = sbi->sb->s_flags;
	struct cp_control cpc;
	int err = 0;
	int ret;
	block_t unusable;

	if (s_flags & SB_RDONLY) {
		f2fs_err(sbi, "checkpoint=disable on readonly fs");
		return -EINVAL;
	}
	sbi->sb->s_flags |= SB_ACTIVE;

	f2fs_update_time(sbi, DISABLE_TIME);

	while (!f2fs_time_over(sbi, DISABLE_TIME)) {
		mutex_lock(&sbi->gc_mutex);
		err = f2fs_gc(sbi, true, false, NULL_SEGNO);
		if (err == -ENODATA) {
			err = 0;
			break;
		}
		if (err && err != -EAGAIN)
			break;
	}

	ret = sync_filesystem(sbi->sb);
	if (ret || err) {
		err = ret ? ret: err;
		goto restore_flag;
	}

	unusable = f2fs_get_unusable_blocks(sbi);
	if (f2fs_disable_cp_again(sbi, unusable)) {
		err = -EAGAIN;
		goto restore_flag;
	}

	mutex_lock(&sbi->gc_mutex);
	cpc.reason = CP_PAUSE;
	set_sbi_flag(sbi, SBI_CP_DISABLED);
	err = f2fs_write_checkpoint(sbi, &cpc);
	if (err)
		goto out_unlock;

	spin_lock(&sbi->stat_lock);
	sbi->unusable_block_count = unusable;
	spin_unlock(&sbi->stat_lock);

out_unlock:
	mutex_unlock(&sbi->gc_mutex);
restore_flag:
	sbi->sb->s_flags = s_flags;	/* Restore MS_RDONLY status */
	return err;
}