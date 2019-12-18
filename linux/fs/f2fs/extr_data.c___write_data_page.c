#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {scalar_t__ for_reclaim; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int submitted; int io_type; int /*<<< orphan*/  need_lock; int /*<<< orphan*/ * last_block; struct bio** bio; struct writeback_control* io_wbc; int /*<<< orphan*/ * encrypted_page; struct page* page; int /*<<< orphan*/  old_blkaddr; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  op; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; struct f2fs_sb_info* sbi; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;
struct TYPE_4__ {int last_disk_size; int /*<<< orphan*/  cp_task; int /*<<< orphan*/  i_sem; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int /*<<< orphan*/  BASE_CHECK ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  DATA ; 
 int EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_HOT_DATA ; 
 int /*<<< orphan*/  IS_NOQUOTA (struct inode*) ; 
 int /*<<< orphan*/  LOCK_DONE ; 
 int /*<<< orphan*/  LOCK_REQ ; 
 int /*<<< orphan*/  LOCK_RETRY ; 
 int /*<<< orphan*/  NULL_ADDR ; 
 unsigned long long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_cold_data (struct page*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int f2fs_do_write_data_page (struct f2fs_io_info*) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 scalar_t__ f2fs_is_drop_cache (struct inode*) ; 
 scalar_t__ f2fs_is_volatile_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_submit_ipu_bio (struct f2fs_sb_info*,struct bio**,struct page*) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_verity_in_progress (struct inode*) ; 
 int f2fs_write_inline_data (struct inode*,struct page*) ; 
 int /*<<< orphan*/  file_set_keep_isize (struct inode*) ; 
 scalar_t__ has_not_enough_free_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dec_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_writepage (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbc_to_write_flags (struct writeback_control*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 

__attribute__((used)) static int __write_data_page(struct page *page, bool *submitted,
				struct bio **bio,
				sector_t *last_block,
				struct writeback_control *wbc,
				enum iostat_type io_type)
{
	struct inode *inode = page->mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	loff_t i_size = i_size_read(inode);
	const pgoff_t end_index = ((unsigned long long) i_size)
							>> PAGE_SHIFT;
	loff_t psize = (page->index + 1) << PAGE_SHIFT;
	unsigned offset = 0;
	bool need_balance_fs = false;
	int err = 0;
	struct f2fs_io_info fio = {
		.sbi = sbi,
		.ino = inode->i_ino,
		.type = DATA,
		.op = REQ_OP_WRITE,
		.op_flags = wbc_to_write_flags(wbc),
		.old_blkaddr = NULL_ADDR,
		.page = page,
		.encrypted_page = NULL,
		.submitted = false,
		.need_lock = LOCK_RETRY,
		.io_type = io_type,
		.io_wbc = wbc,
		.bio = bio,
		.last_block = last_block,
	};

	trace_f2fs_writepage(page, DATA);

	/* we should bypass data pages to proceed the kworkder jobs */
	if (unlikely(f2fs_cp_error(sbi))) {
		mapping_set_error(page->mapping, -EIO);
		/*
		 * don't drop any dirty dentry pages for keeping lastest
		 * directory structure.
		 */
		if (S_ISDIR(inode->i_mode))
			goto redirty_out;
		goto out;
	}

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto redirty_out;

	if (page->index < end_index || f2fs_verity_in_progress(inode))
		goto write;

	/*
	 * If the offset is out-of-range of file size,
	 * this page does not have to be written to disk.
	 */
	offset = i_size & (PAGE_SIZE - 1);
	if ((page->index >= end_index + 1) || !offset)
		goto out;

	zero_user_segment(page, offset, PAGE_SIZE);
write:
	if (f2fs_is_drop_cache(inode))
		goto out;
	/* we should not write 0'th page having journal header */
	if (f2fs_is_volatile_file(inode) && (!page->index ||
			(!wbc->for_reclaim &&
			f2fs_available_free_memory(sbi, BASE_CHECK))))
		goto redirty_out;

	/* Dentry blocks are controlled by checkpoint */
	if (S_ISDIR(inode->i_mode)) {
		fio.need_lock = LOCK_DONE;
		err = f2fs_do_write_data_page(&fio);
		goto done;
	}

	if (!wbc->for_reclaim)
		need_balance_fs = true;
	else if (has_not_enough_free_secs(sbi, 0, 0))
		goto redirty_out;
	else
		set_inode_flag(inode, FI_HOT_DATA);

	err = -EAGAIN;
	if (f2fs_has_inline_data(inode)) {
		err = f2fs_write_inline_data(inode, page);
		if (!err)
			goto out;
	}

	if (err == -EAGAIN) {
		err = f2fs_do_write_data_page(&fio);
		if (err == -EAGAIN) {
			fio.need_lock = LOCK_REQ;
			err = f2fs_do_write_data_page(&fio);
		}
	}

	if (err) {
		file_set_keep_isize(inode);
	} else {
		down_write(&F2FS_I(inode)->i_sem);
		if (F2FS_I(inode)->last_disk_size < psize)
			F2FS_I(inode)->last_disk_size = psize;
		up_write(&F2FS_I(inode)->i_sem);
	}

done:
	if (err && err != -ENOENT)
		goto redirty_out;

out:
	inode_dec_dirty_pages(inode);
	if (err) {
		ClearPageUptodate(page);
		clear_cold_data(page);
	}

	if (wbc->for_reclaim) {
		f2fs_submit_merged_write_cond(sbi, NULL, page, 0, DATA);
		clear_inode_flag(inode, FI_HOT_DATA);
		f2fs_remove_dirty_inode(inode);
		submitted = NULL;
	}

	unlock_page(page);
	if (!S_ISDIR(inode->i_mode) && !IS_NOQUOTA(inode) &&
					!F2FS_I(inode)->cp_task) {
		f2fs_submit_ipu_bio(sbi, bio, page);
		f2fs_balance_fs(sbi, need_balance_fs);
	}

	if (unlikely(f2fs_cp_error(sbi))) {
		f2fs_submit_ipu_bio(sbi, bio, page);
		f2fs_submit_merged_write(sbi, DATA);
		submitted = NULL;
	}

	if (submitted)
		*submitted = fio.submitted;

	return 0;

redirty_out:
	redirty_page_for_writepage(wbc, page);
	/*
	 * pageout() in MM traslates EAGAIN, so calls handle_write_error()
	 * -> mapping_set_error() -> set_bit(AS_EIO, ...).
	 * file_write_and_wait_range() will see EIO error, which is critical
	 * to return value of fsync() followed by atomic_write failure to user.
	 */
	if (!err || wbc->for_reclaim)
		return AOP_WRITEPAGE_ACTIVATE;
	unlock_page(page);
	return err;
}