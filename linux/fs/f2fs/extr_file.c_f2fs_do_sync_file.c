#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int /*<<< orphan*/  for_reclaim; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * wb_sync_req; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum cp_reason_type { ____Placeholder_cp_reason_type } cp_reason_type ;
struct TYPE_8__ {int /*<<< orphan*/  i_sem; } ;
struct TYPE_7__ {scalar_t__ fsync_mode; } ;
struct TYPE_6__ {scalar_t__ min_fsync_blocks; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_INO ; 
 int EIO ; 
 TYPE_4__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 TYPE_3__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FI_APPEND_WRITE ; 
 int /*<<< orphan*/  FI_NEED_IPU ; 
 int /*<<< orphan*/  FI_UPDATE_WRITE ; 
 int /*<<< orphan*/  FLUSH_INO ; 
 scalar_t__ FSYNC_MODE_NOBARRIER ; 
 int /*<<< orphan*/  LONG_MAX ; 
 size_t NODE ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 TYPE_2__* SM_I (struct f2fs_sb_info*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_INO ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int f2fs_cp_error (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_exist_written_data (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int f2fs_fsync_node_pages (struct f2fs_sb_info*,struct inode*,struct writeback_control*,int,unsigned int*) ; 
 int f2fs_issue_flush (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 scalar_t__ f2fs_need_inode_block_update (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_remove_ino_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_skip_inode_update (struct inode*,int) ; 
 int f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_trace_ios (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_wait_on_node_pages_writeback (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_write_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int need_do_checkpoint (struct inode*) ; 
 scalar_t__ need_inode_page_update (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_sync_file_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_f2fs_sync_file_exit (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  try_to_fix_pino (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_do_sync_file(struct file *file, loff_t start, loff_t end,
						int datasync, bool atomic)
{
	struct inode *inode = file->f_mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t ino = inode->i_ino;
	int ret = 0;
	enum cp_reason_type cp_reason = 0;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = LONG_MAX,
		.for_reclaim = 0,
	};
	unsigned int seq_id = 0;

	if (unlikely(f2fs_readonly(inode->i_sb) ||
				is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		return 0;

	trace_f2fs_sync_file_enter(inode);

	if (S_ISDIR(inode->i_mode))
		goto go_write;

	/* if fdatasync is triggered, let's do in-place-update */
	if (datasync || get_dirty_pages(inode) <= SM_I(sbi)->min_fsync_blocks)
		set_inode_flag(inode, FI_NEED_IPU);
	ret = file_write_and_wait_range(file, start, end);
	clear_inode_flag(inode, FI_NEED_IPU);

	if (ret) {
		trace_f2fs_sync_file_exit(inode, cp_reason, datasync, ret);
		return ret;
	}

	/* if the inode is dirty, let's recover all the time */
	if (!f2fs_skip_inode_update(inode, datasync)) {
		f2fs_write_inode(inode, NULL);
		goto go_write;
	}

	/*
	 * if there is no written data, don't waste time to write recovery info.
	 */
	if (!is_inode_flag_set(inode, FI_APPEND_WRITE) &&
			!f2fs_exist_written_data(sbi, ino, APPEND_INO)) {

		/* it may call write_inode just prior to fsync */
		if (need_inode_page_update(sbi, ino))
			goto go_write;

		if (is_inode_flag_set(inode, FI_UPDATE_WRITE) ||
				f2fs_exist_written_data(sbi, ino, UPDATE_INO))
			goto flush_out;
		goto out;
	}
go_write:
	/*
	 * Both of fdatasync() and fsync() are able to be recovered from
	 * sudden-power-off.
	 */
	down_read(&F2FS_I(inode)->i_sem);
	cp_reason = need_do_checkpoint(inode);
	up_read(&F2FS_I(inode)->i_sem);

	if (cp_reason) {
		/* all the dirty node pages should be flushed for POR */
		ret = f2fs_sync_fs(inode->i_sb, 1);

		/*
		 * We've secured consistency through sync_fs. Following pino
		 * will be used only for fsynced inodes after checkpoint.
		 */
		try_to_fix_pino(inode);
		clear_inode_flag(inode, FI_APPEND_WRITE);
		clear_inode_flag(inode, FI_UPDATE_WRITE);
		goto out;
	}
sync_nodes:
	atomic_inc(&sbi->wb_sync_req[NODE]);
	ret = f2fs_fsync_node_pages(sbi, inode, &wbc, atomic, &seq_id);
	atomic_dec(&sbi->wb_sync_req[NODE]);
	if (ret)
		goto out;

	/* if cp_error was enabled, we should avoid infinite loop */
	if (unlikely(f2fs_cp_error(sbi))) {
		ret = -EIO;
		goto out;
	}

	if (f2fs_need_inode_block_update(sbi, ino)) {
		f2fs_mark_inode_dirty_sync(inode, true);
		f2fs_write_inode(inode, NULL);
		goto sync_nodes;
	}

	/*
	 * If it's atomic_write, it's just fine to keep write ordering. So
	 * here we don't need to wait for node write completion, since we use
	 * node chain which serializes node blocks. If one of node writes are
	 * reordered, we can see simply broken chain, resulting in stopping
	 * roll-forward recovery. It means we'll recover all or none node blocks
	 * given fsync mark.
	 */
	if (!atomic) {
		ret = f2fs_wait_on_node_pages_writeback(sbi, seq_id);
		if (ret)
			goto out;
	}

	/* once recovery info is written, don't need to tack this */
	f2fs_remove_ino_entry(sbi, ino, APPEND_INO);
	clear_inode_flag(inode, FI_APPEND_WRITE);
flush_out:
	if (!atomic && F2FS_OPTION(sbi).fsync_mode != FSYNC_MODE_NOBARRIER)
		ret = f2fs_issue_flush(sbi, inode->i_ino);
	if (!ret) {
		f2fs_remove_ino_entry(sbi, ino, UPDATE_INO);
		clear_inode_flag(inode, FI_UPDATE_WRITE);
		f2fs_remove_ino_entry(sbi, ino, FLUSH_INO);
	}
	f2fs_update_time(sbi, REQ_TIME);
out:
	trace_f2fs_sync_file_exit(inode, cp_reason, datasync, ret);
	f2fs_trace_ios(NULL, 1);
	return ret;
}