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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct f2fs_sb_info {int /*<<< orphan*/  s_encoding; struct f2fs_sb_info** write_io; int /*<<< orphan*/  write_io_dummy; struct f2fs_sb_info* raw_super; scalar_t__ s_chksum_driver; struct f2fs_sb_info* ckpt; int /*<<< orphan*/ * meta_inode; int /*<<< orphan*/ * node_inode; int /*<<< orphan*/  fsync_node_num; int /*<<< orphan*/  umount_mutex; int /*<<< orphan*/  discard_blks; } ;
struct cp_control {int reason; } ;
struct TYPE_2__ {struct f2fs_sb_info** s_qf_names; } ;

/* Variables and functions */
 int CP_TRIMMED ; 
 int CP_UMOUNT ; 
 int /*<<< orphan*/  CP_UMOUNT_FLAG ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int MAXQUOTAS ; 
 int NR_PAGE_TYPE ; 
 int /*<<< orphan*/  SBI_IS_DIRTY ; 
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 int /*<<< orphan*/  destroy_device_list (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_percpu_info (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_destroy_node_manager (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_destroy_segment_manager (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_destroy_stats (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_flush_merged_writes (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_hw_should_discard (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_hw_support_discard (struct f2fs_sb_info*) ; 
 int f2fs_issue_discard_timeout (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_leave_shrinker (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_quota_off_umount (struct super_block*) ; 
 int /*<<< orphan*/  f2fs_release_ino_entry (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_unregister_sysfs (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_wait_on_all_pages_writeback (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_write_checkpoint (struct f2fs_sb_info*,struct cp_control*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_unload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_put_super(struct super_block *sb)
{
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	int i;
	bool dropped;

	f2fs_quota_off_umount(sb);

	/* prevent remaining shrinker jobs */
	mutex_lock(&sbi->umount_mutex);

	/*
	 * We don't need to do checkpoint when superblock is clean.
	 * But, the previous checkpoint was not done by umount, it needs to do
	 * clean checkpoint again.
	 */
	if ((is_sbi_flag_set(sbi, SBI_IS_DIRTY) ||
			!is_set_ckpt_flags(sbi, CP_UMOUNT_FLAG))) {
		struct cp_control cpc = {
			.reason = CP_UMOUNT,
		};
		f2fs_write_checkpoint(sbi, &cpc);
	}

	/* be sure to wait for any on-going discard commands */
	dropped = f2fs_issue_discard_timeout(sbi);

	if ((f2fs_hw_support_discard(sbi) || f2fs_hw_should_discard(sbi)) &&
					!sbi->discard_blks && !dropped) {
		struct cp_control cpc = {
			.reason = CP_UMOUNT | CP_TRIMMED,
		};
		f2fs_write_checkpoint(sbi, &cpc);
	}

	/*
	 * normally superblock is clean, so we need to release this.
	 * In addition, EIO will skip do checkpoint, we need this as well.
	 */
	f2fs_release_ino_entry(sbi, true);

	f2fs_leave_shrinker(sbi);
	mutex_unlock(&sbi->umount_mutex);

	/* our cp_error case, we can wait for any writeback page */
	f2fs_flush_merged_writes(sbi);

	f2fs_wait_on_all_pages_writeback(sbi);

	f2fs_bug_on(sbi, sbi->fsync_node_num);

	iput(sbi->node_inode);
	sbi->node_inode = NULL;

	iput(sbi->meta_inode);
	sbi->meta_inode = NULL;

	/*
	 * iput() can update stat information, if f2fs_write_checkpoint()
	 * above failed with error.
	 */
	f2fs_destroy_stats(sbi);

	/* destroy f2fs internal modules */
	f2fs_destroy_node_manager(sbi);
	f2fs_destroy_segment_manager(sbi);

	kvfree(sbi->ckpt);

	f2fs_unregister_sysfs(sbi);

	sb->s_fs_info = NULL;
	if (sbi->s_chksum_driver)
		crypto_free_shash(sbi->s_chksum_driver);
	kvfree(sbi->raw_super);

	destroy_device_list(sbi);
	mempool_destroy(sbi->write_io_dummy);
#ifdef CONFIG_QUOTA
	for (i = 0; i < MAXQUOTAS; i++)
		kvfree(F2FS_OPTION(sbi).s_qf_names[i]);
#endif
	destroy_percpu_info(sbi);
	for (i = 0; i < NR_PAGE_TYPE; i++)
		kvfree(sbi->write_io[i]);
#ifdef CONFIG_UNICODE
	utf8_unload(sbi->s_encoding);
#endif
	kvfree(sbi);
}