#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_io_info {int /*<<< orphan*/  io_type; int /*<<< orphan*/  need_lock; int /*<<< orphan*/ * encrypted_page; struct page* page; int /*<<< orphan*/  old_blkaddr; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  op; int /*<<< orphan*/  temp; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; TYPE_1__* sbi; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/ * i_gc_failures; } ;
struct TYPE_4__ {int /*<<< orphan*/ * skipped_atomic_files; } ;

/* Variables and functions */
 int BG_GC ; 
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  COLD ; 
 int /*<<< orphan*/  DATA ; 
 int EAGAIN ; 
 int ENOENT ; 
 int ENOMEM ; 
 TYPE_3__* F2FS_I (struct inode*) ; 
 TYPE_1__* F2FS_I_SB (struct inode*) ; 
 int FG_GC ; 
 int /*<<< orphan*/  FS_GC_DATA_IO ; 
 size_t GC_FAILURE_ATOMIC ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  LOCK_REQ ; 
 int /*<<< orphan*/  NULL_ADDR ; 
 int PTR_ERR (struct page*) ; 
 int PageDirty (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  check_valid_map (TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  clear_cold_data (struct page*) ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int f2fs_do_write_data_page (struct f2fs_io_info*) ; 
 struct page* f2fs_get_lock_data_page (struct inode*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_pinned_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_pin_file_control (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  inode_dec_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  set_cold_data (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static int move_data_page(struct inode *inode, block_t bidx, int gc_type,
							unsigned int segno, int off)
{
	struct page *page;
	int err = 0;

	page = f2fs_get_lock_data_page(inode, bidx, true);
	if (IS_ERR(page))
		return PTR_ERR(page);

	if (!check_valid_map(F2FS_I_SB(inode), segno, off)) {
		err = -ENOENT;
		goto out;
	}

	if (f2fs_is_atomic_file(inode)) {
		F2FS_I(inode)->i_gc_failures[GC_FAILURE_ATOMIC]++;
		F2FS_I_SB(inode)->skipped_atomic_files[gc_type]++;
		err = -EAGAIN;
		goto out;
	}
	if (f2fs_is_pinned_file(inode)) {
		if (gc_type == FG_GC)
			f2fs_pin_file_control(inode, true);
		err = -EAGAIN;
		goto out;
	}

	if (gc_type == BG_GC) {
		if (PageWriteback(page)) {
			err = -EAGAIN;
			goto out;
		}
		set_page_dirty(page);
		set_cold_data(page);
	} else {
		struct f2fs_io_info fio = {
			.sbi = F2FS_I_SB(inode),
			.ino = inode->i_ino,
			.type = DATA,
			.temp = COLD,
			.op = REQ_OP_WRITE,
			.op_flags = REQ_SYNC,
			.old_blkaddr = NULL_ADDR,
			.page = page,
			.encrypted_page = NULL,
			.need_lock = LOCK_REQ,
			.io_type = FS_GC_DATA_IO,
		};
		bool is_dirty = PageDirty(page);

retry:
		f2fs_wait_on_page_writeback(page, DATA, true, true);

		set_page_dirty(page);
		if (clear_page_dirty_for_io(page)) {
			inode_dec_dirty_pages(inode);
			f2fs_remove_dirty_inode(inode);
		}

		set_cold_data(page);

		err = f2fs_do_write_data_page(&fio);
		if (err) {
			clear_cold_data(page);
			if (err == -ENOMEM) {
				congestion_wait(BLK_RW_ASYNC, HZ/50);
				goto retry;
			}
			if (is_dirty)
				set_page_dirty(page);
		}
	}
out:
	f2fs_put_page(page, 1);
	return err;
}