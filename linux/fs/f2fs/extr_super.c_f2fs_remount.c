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
struct super_block {unsigned long s_flags; } ;
struct f2fs_mount_info {scalar_t__ whint_mode; int /*<<< orphan*/ ** s_qf_names; int /*<<< orphan*/  s_jquota_fmt; } ;
struct f2fs_sb_info {struct f2fs_mount_info mount_opt; scalar_t__ gc_thread; } ;
struct TYPE_2__ {scalar_t__ whint_mode; int /*<<< orphan*/ ** s_qf_names; int /*<<< orphan*/  s_jquota_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_GC ; 
 int /*<<< orphan*/  DISABLE_CHECKPOINT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_CACHE ; 
 int /*<<< orphan*/  F2FS_IO_ALIGNED (struct f2fs_sb_info*) ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  FLUSH_MERGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int /*<<< orphan*/  SBI_IS_CLOSE ; 
 int /*<<< orphan*/  SBI_IS_DIRTY ; 
 int /*<<< orphan*/  SBI_NEED_SB_WRITE ; 
 int SB_LAZYTIME ; 
 int SB_POSIXACL ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  WB_REASON_SYNC ; 
 int /*<<< orphan*/  clear_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_options (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  dquot_resume (struct super_block*,int) ; 
 int dquot_suspend (struct super_block*,int) ; 
 int f2fs_commit_super (struct f2fs_sb_info*,int) ; 
 int f2fs_create_flush_cmd_control (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_destroy_flush_cmd_control (struct f2fs_sb_info*,int) ; 
 int f2fs_disable_checkpoint (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_enable_checkpoint (struct f2fs_sb_info*) ; 
 int f2fs_enable_quotas (struct super_block*) ; 
 int /*<<< orphan*/  f2fs_info (struct f2fs_sb_info*,char*,int) ; 
 scalar_t__ f2fs_readonly (struct super_block*) ; 
 scalar_t__ f2fs_sb_has_quota_ino (struct f2fs_sb_info*) ; 
 int f2fs_start_gc_thread (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_stop_gc_thread (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_sync_fs (struct super_block*,int) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  limit_reserve_root (struct f2fs_sb_info*) ; 
 int parse_options (struct super_block*,char*) ; 
 scalar_t__ sb_any_quota_suspended (struct super_block*) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_inodes_sb (struct super_block*) ; 
 int test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeback_inodes_sb (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_remount(struct super_block *sb, int *flags, char *data)
{
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	struct f2fs_mount_info org_mount_opt;
	unsigned long old_sb_flags;
	int err;
	bool need_restart_gc = false;
	bool need_stop_gc = false;
	bool no_extent_cache = !test_opt(sbi, EXTENT_CACHE);
	bool disable_checkpoint = test_opt(sbi, DISABLE_CHECKPOINT);
	bool no_io_align = !F2FS_IO_ALIGNED(sbi);
	bool checkpoint_changed;
#ifdef CONFIG_QUOTA
	int i, j;
#endif

	/*
	 * Save the old mount options in case we
	 * need to restore them.
	 */
	org_mount_opt = sbi->mount_opt;
	old_sb_flags = sb->s_flags;

#ifdef CONFIG_QUOTA
	org_mount_opt.s_jquota_fmt = F2FS_OPTION(sbi).s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++) {
		if (F2FS_OPTION(sbi).s_qf_names[i]) {
			org_mount_opt.s_qf_names[i] =
				kstrdup(F2FS_OPTION(sbi).s_qf_names[i],
				GFP_KERNEL);
			if (!org_mount_opt.s_qf_names[i]) {
				for (j = 0; j < i; j++)
					kvfree(org_mount_opt.s_qf_names[j]);
				return -ENOMEM;
			}
		} else {
			org_mount_opt.s_qf_names[i] = NULL;
		}
	}
#endif

	/* recover superblocks we couldn't write due to previous RO mount */
	if (!(*flags & SB_RDONLY) && is_sbi_flag_set(sbi, SBI_NEED_SB_WRITE)) {
		err = f2fs_commit_super(sbi, false);
		f2fs_info(sbi, "Try to recover all the superblocks, ret: %d",
			  err);
		if (!err)
			clear_sbi_flag(sbi, SBI_NEED_SB_WRITE);
	}

	default_options(sbi);

	/* parse mount options */
	err = parse_options(sb, data);
	if (err)
		goto restore_opts;
	checkpoint_changed =
			disable_checkpoint != test_opt(sbi, DISABLE_CHECKPOINT);

	/*
	 * Previous and new state of filesystem is RO,
	 * so skip checking GC and FLUSH_MERGE conditions.
	 */
	if (f2fs_readonly(sb) && (*flags & SB_RDONLY))
		goto skip;

#ifdef CONFIG_QUOTA
	if (!f2fs_readonly(sb) && (*flags & SB_RDONLY)) {
		err = dquot_suspend(sb, -1);
		if (err < 0)
			goto restore_opts;
	} else if (f2fs_readonly(sb) && !(*flags & SB_RDONLY)) {
		/* dquot_resume needs RW */
		sb->s_flags &= ~SB_RDONLY;
		if (sb_any_quota_suspended(sb)) {
			dquot_resume(sb, -1);
		} else if (f2fs_sb_has_quota_ino(sbi)) {
			err = f2fs_enable_quotas(sb);
			if (err)
				goto restore_opts;
		}
	}
#endif
	/* disallow enable/disable extent_cache dynamically */
	if (no_extent_cache == !!test_opt(sbi, EXTENT_CACHE)) {
		err = -EINVAL;
		f2fs_warn(sbi, "switch extent_cache option is not allowed");
		goto restore_opts;
	}

	if (no_io_align == !!F2FS_IO_ALIGNED(sbi)) {
		err = -EINVAL;
		f2fs_warn(sbi, "switch io_bits option is not allowed");
		goto restore_opts;
	}

	if ((*flags & SB_RDONLY) && test_opt(sbi, DISABLE_CHECKPOINT)) {
		err = -EINVAL;
		f2fs_warn(sbi, "disabling checkpoint not compatible with read-only");
		goto restore_opts;
	}

	/*
	 * We stop the GC thread if FS is mounted as RO
	 * or if background_gc = off is passed in mount
	 * option. Also sync the filesystem.
	 */
	if ((*flags & SB_RDONLY) || !test_opt(sbi, BG_GC)) {
		if (sbi->gc_thread) {
			f2fs_stop_gc_thread(sbi);
			need_restart_gc = true;
		}
	} else if (!sbi->gc_thread) {
		err = f2fs_start_gc_thread(sbi);
		if (err)
			goto restore_opts;
		need_stop_gc = true;
	}

	if (*flags & SB_RDONLY ||
		F2FS_OPTION(sbi).whint_mode != org_mount_opt.whint_mode) {
		writeback_inodes_sb(sb, WB_REASON_SYNC);
		sync_inodes_sb(sb);

		set_sbi_flag(sbi, SBI_IS_DIRTY);
		set_sbi_flag(sbi, SBI_IS_CLOSE);
		f2fs_sync_fs(sb, 1);
		clear_sbi_flag(sbi, SBI_IS_CLOSE);
	}

	if (checkpoint_changed) {
		if (test_opt(sbi, DISABLE_CHECKPOINT)) {
			err = f2fs_disable_checkpoint(sbi);
			if (err)
				goto restore_gc;
		} else {
			f2fs_enable_checkpoint(sbi);
		}
	}

	/*
	 * We stop issue flush thread if FS is mounted as RO
	 * or if flush_merge is not passed in mount option.
	 */
	if ((*flags & SB_RDONLY) || !test_opt(sbi, FLUSH_MERGE)) {
		clear_opt(sbi, FLUSH_MERGE);
		f2fs_destroy_flush_cmd_control(sbi, false);
	} else {
		err = f2fs_create_flush_cmd_control(sbi);
		if (err)
			goto restore_gc;
	}
skip:
#ifdef CONFIG_QUOTA
	/* Release old quota file names */
	for (i = 0; i < MAXQUOTAS; i++)
		kvfree(org_mount_opt.s_qf_names[i]);
#endif
	/* Update the POSIXACL Flag */
	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sbi, POSIX_ACL) ? SB_POSIXACL : 0);

	limit_reserve_root(sbi);
	*flags = (*flags & ~SB_LAZYTIME) | (sb->s_flags & SB_LAZYTIME);
	return 0;
restore_gc:
	if (need_restart_gc) {
		if (f2fs_start_gc_thread(sbi))
			f2fs_warn(sbi, "background gc thread has stopped");
	} else if (need_stop_gc) {
		f2fs_stop_gc_thread(sbi);
	}
restore_opts:
#ifdef CONFIG_QUOTA
	F2FS_OPTION(sbi).s_jquota_fmt = org_mount_opt.s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++) {
		kvfree(F2FS_OPTION(sbi).s_qf_names[i]);
		F2FS_OPTION(sbi).s_qf_names[i] = org_mount_opt.s_qf_names[i];
	}
#endif
	sbi->mount_opt = org_mount_opt;
	sb->s_flags = old_sb_flags;
	return err;
}