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
struct writeback_control {scalar_t__ sync_mode; int /*<<< orphan*/  pages_skipped; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * wb_sync_req; int /*<<< orphan*/  writepages; } ;
struct blk_plug {int dummy; } ;
struct address_space {struct inode* host; TYPE_1__* a_ops; } ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;
struct TYPE_2__ {int /*<<< orphan*/  writepage; } ;

/* Variables and functions */
 size_t DATA ; 
 int /*<<< orphan*/  DIRTY_DENTS ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_DO_DEFRAG ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ WB_SYNC_NONE ; 
 scalar_t__ __should_serialize_io (struct inode*,struct writeback_control*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 scalar_t__ f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int f2fs_write_cache_pages (struct address_space*,struct writeback_control*,int) ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nr_pages_to_skip (struct f2fs_sb_info*,size_t) ; 
 int /*<<< orphan*/  trace_f2fs_writepages (struct inode*,struct writeback_control*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __f2fs_write_data_pages(struct address_space *mapping,
						struct writeback_control *wbc,
						enum iostat_type io_type)
{
	struct inode *inode = mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct blk_plug plug;
	int ret;
	bool locked = false;

	/* deal with chardevs and other special file */
	if (!mapping->a_ops->writepage)
		return 0;

	/* skip writing if there is no dirty page in this inode */
	if (!get_dirty_pages(inode) && wbc->sync_mode == WB_SYNC_NONE)
		return 0;

	/* during POR, we don't need to trigger writepage at all. */
	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto skip_write;

	if ((S_ISDIR(inode->i_mode) || IS_NOQUOTA(inode)) &&
			wbc->sync_mode == WB_SYNC_NONE &&
			get_dirty_pages(inode) < nr_pages_to_skip(sbi, DATA) &&
			f2fs_available_free_memory(sbi, DIRTY_DENTS))
		goto skip_write;

	/* skip writing during file defragment */
	if (is_inode_flag_set(inode, FI_DO_DEFRAG))
		goto skip_write;

	trace_f2fs_writepages(mapping->host, wbc, DATA);

	/* to avoid spliting IOs due to mixed WB_SYNC_ALL and WB_SYNC_NONE */
	if (wbc->sync_mode == WB_SYNC_ALL)
		atomic_inc(&sbi->wb_sync_req[DATA]);
	else if (atomic_read(&sbi->wb_sync_req[DATA]))
		goto skip_write;

	if (__should_serialize_io(inode, wbc)) {
		mutex_lock(&sbi->writepages);
		locked = true;
	}

	blk_start_plug(&plug);
	ret = f2fs_write_cache_pages(mapping, wbc, io_type);
	blk_finish_plug(&plug);

	if (locked)
		mutex_unlock(&sbi->writepages);

	if (wbc->sync_mode == WB_SYNC_ALL)
		atomic_dec(&sbi->wb_sync_req[DATA]);
	/*
	 * if some pages were truncated, we cannot guarantee its mapping->host
	 * to detect pending bios.
	 */

	f2fs_remove_dirty_inode(inode);
	return ret;

skip_write:
	wbc->pages_skipped += get_dirty_pages(inode);
	trace_f2fs_writepages(mapping->host, wbc, DATA);
	return 0;
}