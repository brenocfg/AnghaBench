#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct page {scalar_t__ mapping; scalar_t__ index; } ;
struct node_info {int /*<<< orphan*/  version; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_ino; } ;
struct f2fs_summary {int dummy; } ;
struct f2fs_io_info {int in_list; int retry; scalar_t__ new_blkaddr; scalar_t__ old_blkaddr; TYPE_1__* sbi; struct page* encrypted_page; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  op; struct page* page; int /*<<< orphan*/  temp; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; } ;
struct dnode_of_data {scalar_t__ data_blkaddr; struct page* node_page; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; } ;
typedef  scalar_t__ block_t ;
struct TYPE_12__ {int /*<<< orphan*/  io_order_lock; int /*<<< orphan*/ * skipped_atomic_files; } ;
struct TYPE_11__ {int /*<<< orphan*/ * i_gc_failures; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLD ; 
 int /*<<< orphan*/  CURSEG_COLD_DATA ; 
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  DATA ; 
 int EAGAIN ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 int /*<<< orphan*/  F2FS_DIRTY_META ; 
 TYPE_10__* F2FS_I (struct inode*) ; 
 TYPE_1__* F2FS_I_SB (struct inode*) ; 
 int FGP_CREAT ; 
 int FGP_LOCK ; 
 int /*<<< orphan*/  FI_APPEND_WRITE ; 
 int /*<<< orphan*/  FI_FIRST_BLOCK_WRITTEN ; 
 int /*<<< orphan*/  FS_GC_DATA_IO ; 
 size_t GC_FAILURE_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 scalar_t__ META_MAPPING (TYPE_1__*) ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  check_valid_map (TYPE_1__*,unsigned int,int) ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  dec_page_count (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  f2fs_allocate_data_block (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  f2fs_do_replace_block (TYPE_1__*,struct f2fs_summary*,scalar_t__,scalar_t__,int,int) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int f2fs_get_node_info (TYPE_1__*,int /*<<< orphan*/ ,struct node_info*) ; 
 struct page* f2fs_grab_cache_page (scalar_t__,scalar_t__,int) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_pinned_file (struct inode*) ; 
 struct page* f2fs_pagecache_get_page (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_pin_file_control (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int f2fs_submit_page_bio (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_submit_page_write (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_update_data_blkaddr (struct dnode_of_data*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_update_iostat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_block_writeback (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  set_summary (struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int move_data_block(struct inode *inode, block_t bidx,
				int gc_type, unsigned int segno, int off)
{
	struct f2fs_io_info fio = {
		.sbi = F2FS_I_SB(inode),
		.ino = inode->i_ino,
		.type = DATA,
		.temp = COLD,
		.op = REQ_OP_READ,
		.op_flags = 0,
		.encrypted_page = NULL,
		.in_list = false,
		.retry = false,
	};
	struct dnode_of_data dn;
	struct f2fs_summary sum;
	struct node_info ni;
	struct page *page, *mpage;
	block_t newaddr;
	int err = 0;
	bool lfs_mode = test_opt(fio.sbi, LFS);

	/* do not read out */
	page = f2fs_grab_cache_page(inode->i_mapping, bidx, false);
	if (!page)
		return -ENOMEM;

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
		f2fs_pin_file_control(inode, true);
		err = -EAGAIN;
		goto out;
	}

	set_new_dnode(&dn, inode, NULL, NULL, 0);
	err = f2fs_get_dnode_of_data(&dn, bidx, LOOKUP_NODE);
	if (err)
		goto out;

	if (unlikely(dn.data_blkaddr == NULL_ADDR)) {
		ClearPageUptodate(page);
		err = -ENOENT;
		goto put_out;
	}

	/*
	 * don't cache encrypted data into meta inode until previous dirty
	 * data were writebacked to avoid racing between GC and flush.
	 */
	f2fs_wait_on_page_writeback(page, DATA, true, true);

	f2fs_wait_on_block_writeback(inode, dn.data_blkaddr);

	err = f2fs_get_node_info(fio.sbi, dn.nid, &ni);
	if (err)
		goto put_out;

	set_summary(&sum, dn.nid, dn.ofs_in_node, ni.version);

	/* read page */
	fio.page = page;
	fio.new_blkaddr = fio.old_blkaddr = dn.data_blkaddr;

	if (lfs_mode)
		down_write(&fio.sbi->io_order_lock);

	mpage = f2fs_grab_cache_page(META_MAPPING(fio.sbi),
					fio.old_blkaddr, false);
	if (!mpage)
		goto up_out;

	fio.encrypted_page = mpage;

	/* read source block in mpage */
	if (!PageUptodate(mpage)) {
		err = f2fs_submit_page_bio(&fio);
		if (err) {
			f2fs_put_page(mpage, 1);
			goto up_out;
		}
		lock_page(mpage);
		if (unlikely(mpage->mapping != META_MAPPING(fio.sbi) ||
						!PageUptodate(mpage))) {
			err = -EIO;
			f2fs_put_page(mpage, 1);
			goto up_out;
		}
	}

	f2fs_allocate_data_block(fio.sbi, NULL, fio.old_blkaddr, &newaddr,
					&sum, CURSEG_COLD_DATA, NULL, false);

	fio.encrypted_page = f2fs_pagecache_get_page(META_MAPPING(fio.sbi),
				newaddr, FGP_LOCK | FGP_CREAT, GFP_NOFS);
	if (!fio.encrypted_page) {
		err = -ENOMEM;
		f2fs_put_page(mpage, 1);
		goto recover_block;
	}

	/* write target block */
	f2fs_wait_on_page_writeback(fio.encrypted_page, DATA, true, true);
	memcpy(page_address(fio.encrypted_page),
				page_address(mpage), PAGE_SIZE);
	f2fs_put_page(mpage, 1);
	invalidate_mapping_pages(META_MAPPING(fio.sbi),
				fio.old_blkaddr, fio.old_blkaddr);

	set_page_dirty(fio.encrypted_page);
	if (clear_page_dirty_for_io(fio.encrypted_page))
		dec_page_count(fio.sbi, F2FS_DIRTY_META);

	set_page_writeback(fio.encrypted_page);
	ClearPageError(page);

	/* allocate block address */
	f2fs_wait_on_page_writeback(dn.node_page, NODE, true, true);

	fio.op = REQ_OP_WRITE;
	fio.op_flags = REQ_SYNC;
	fio.new_blkaddr = newaddr;
	f2fs_submit_page_write(&fio);
	if (fio.retry) {
		err = -EAGAIN;
		if (PageWriteback(fio.encrypted_page))
			end_page_writeback(fio.encrypted_page);
		goto put_page_out;
	}

	f2fs_update_iostat(fio.sbi, FS_GC_DATA_IO, F2FS_BLKSIZE);

	f2fs_update_data_blkaddr(&dn, newaddr);
	set_inode_flag(inode, FI_APPEND_WRITE);
	if (page->index == 0)
		set_inode_flag(inode, FI_FIRST_BLOCK_WRITTEN);
put_page_out:
	f2fs_put_page(fio.encrypted_page, 1);
recover_block:
	if (err)
		f2fs_do_replace_block(fio.sbi, &sum, newaddr, fio.old_blkaddr,
								true, true);
up_out:
	if (lfs_mode)
		up_write(&fio.sbi->io_order_lock);
put_out:
	f2fs_put_dnode(&dn);
out:
	f2fs_put_page(page, 1);
	return err;
}