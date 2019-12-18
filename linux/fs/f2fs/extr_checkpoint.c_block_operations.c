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
struct writeback_control {int /*<<< orphan*/  for_reclaim; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct f2fs_sb_info {int /*<<< orphan*/  node_change; int /*<<< orphan*/ * wb_sync_req; int /*<<< orphan*/  node_write; TYPE_1__* sb; } ;
struct blk_plug {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int DEFAULT_RETRY_QUOTA_FLUSH_COUNT ; 
 int /*<<< orphan*/  DIR_INODE ; 
 int /*<<< orphan*/  F2FS_DIRTY_DENTS ; 
 int /*<<< orphan*/  F2FS_DIRTY_IMETA ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 int /*<<< orphan*/  FS_CP_NODE_IO ; 
 int /*<<< orphan*/  LONG_MAX ; 
 size_t NODE ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_FLUSH ; 
 int /*<<< orphan*/  SBI_QUOTA_SKIP_FLUSH ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 scalar_t__ __need_flush_quota (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __prepare_cp_block (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_lock_all (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_quota_sync (TYPE_1__*,int) ; 
 int f2fs_sync_dirty_inodes (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_sync_inode_meta (struct f2fs_sb_info*) ; 
 int f2fs_sync_node_pages (struct f2fs_sb_info*,struct writeback_control*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_unlock_all (struct f2fs_sb_info*) ; 
 scalar_t__ get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int block_operations(struct f2fs_sb_info *sbi)
{
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = LONG_MAX,
		.for_reclaim = 0,
	};
	struct blk_plug plug;
	int err = 0, cnt = 0;

	blk_start_plug(&plug);

retry_flush_quotas:
	f2fs_lock_all(sbi);
	if (__need_flush_quota(sbi)) {
		int locked;

		if (++cnt > DEFAULT_RETRY_QUOTA_FLUSH_COUNT) {
			set_sbi_flag(sbi, SBI_QUOTA_SKIP_FLUSH);
			set_sbi_flag(sbi, SBI_QUOTA_NEED_FLUSH);
			goto retry_flush_dents;
		}
		f2fs_unlock_all(sbi);

		/* only failed during mount/umount/freeze/quotactl */
		locked = down_read_trylock(&sbi->sb->s_umount);
		f2fs_quota_sync(sbi->sb, -1);
		if (locked)
			up_read(&sbi->sb->s_umount);
		cond_resched();
		goto retry_flush_quotas;
	}

retry_flush_dents:
	/* write all the dirty dentry pages */
	if (get_pages(sbi, F2FS_DIRTY_DENTS)) {
		f2fs_unlock_all(sbi);
		err = f2fs_sync_dirty_inodes(sbi, DIR_INODE);
		if (err)
			goto out;
		cond_resched();
		goto retry_flush_quotas;
	}

	/*
	 * POR: we should ensure that there are no dirty node pages
	 * until finishing nat/sit flush. inode->i_blocks can be updated.
	 */
	down_write(&sbi->node_change);

	if (get_pages(sbi, F2FS_DIRTY_IMETA)) {
		up_write(&sbi->node_change);
		f2fs_unlock_all(sbi);
		err = f2fs_sync_inode_meta(sbi);
		if (err)
			goto out;
		cond_resched();
		goto retry_flush_quotas;
	}

retry_flush_nodes:
	down_write(&sbi->node_write);

	if (get_pages(sbi, F2FS_DIRTY_NODES)) {
		up_write(&sbi->node_write);
		atomic_inc(&sbi->wb_sync_req[NODE]);
		err = f2fs_sync_node_pages(sbi, &wbc, false, FS_CP_NODE_IO);
		atomic_dec(&sbi->wb_sync_req[NODE]);
		if (err) {
			up_write(&sbi->node_change);
			f2fs_unlock_all(sbi);
			goto out;
		}
		cond_resched();
		goto retry_flush_nodes;
	}

	/*
	 * sbi->node_change is used only for AIO write_begin path which produces
	 * dirty node blocks and some checkpoint values by block allocation.
	 */
	__prepare_cp_block(sbi);
	up_write(&sbi->node_change);
out:
	blk_finish_plug(&plug);
	return err;
}