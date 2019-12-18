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
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ pgoff_t ;
typedef  unsigned int loff_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE_READ ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int FGP_CREAT ; 
 int FGP_LOCK ; 
 int FGP_WRITE ; 
 int /*<<< orphan*/  FI_ATOMIC_REVOKE_REQUEST ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INMEM_PAGES ; 
 int /*<<< orphan*/  IS_NOQUOTA (struct inode*) ; 
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 
 unsigned long long PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_inmem_pages_all (struct f2fs_sb_info*,int) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct page* f2fs_pagecache_get_page (struct address_space*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int f2fs_submit_page_read (struct inode*,struct page*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_verity_in_progress (struct inode*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  f2fs_write_failed (struct address_space*,unsigned int) ; 
 scalar_t__ has_not_enough_free_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int i_size_read (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int prepare_write_begin (struct f2fs_sb_info*,struct page*,unsigned int,unsigned int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  trace_f2fs_write_begin (struct inode*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int f2fs_write_begin(struct file *file, struct address_space *mapping,
		loff_t pos, unsigned len, unsigned flags,
		struct page **pagep, void **fsdata)
{
	struct inode *inode = mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct page *page = NULL;
	pgoff_t index = ((unsigned long long) pos) >> PAGE_SHIFT;
	bool need_balance = false, drop_atomic = false;
	block_t blkaddr = NULL_ADDR;
	int err = 0;

	trace_f2fs_write_begin(inode, pos, len, flags);

	if (!f2fs_is_checkpoint_ready(sbi)) {
		err = -ENOSPC;
		goto fail;
	}

	if ((f2fs_is_atomic_file(inode) &&
			!f2fs_available_free_memory(sbi, INMEM_PAGES)) ||
			is_inode_flag_set(inode, FI_ATOMIC_REVOKE_REQUEST)) {
		err = -ENOMEM;
		drop_atomic = true;
		goto fail;
	}

	/*
	 * We should check this at this moment to avoid deadlock on inode page
	 * and #0 page. The locking rule for inline_data conversion should be:
	 * lock_page(page #0) -> lock_page(inode_page)
	 */
	if (index != 0) {
		err = f2fs_convert_inline_inode(inode);
		if (err)
			goto fail;
	}
repeat:
	/*
	 * Do not use grab_cache_page_write_begin() to avoid deadlock due to
	 * wait_for_stable_page. Will wait that below with our IO control.
	 */
	page = f2fs_pagecache_get_page(mapping, index,
				FGP_LOCK | FGP_WRITE | FGP_CREAT, GFP_NOFS);
	if (!page) {
		err = -ENOMEM;
		goto fail;
	}

	*pagep = page;

	err = prepare_write_begin(sbi, page, pos, len,
					&blkaddr, &need_balance);
	if (err)
		goto fail;

	if (need_balance && !IS_NOQUOTA(inode) &&
			has_not_enough_free_secs(sbi, 0, 0)) {
		unlock_page(page);
		f2fs_balance_fs(sbi, true);
		lock_page(page);
		if (page->mapping != mapping) {
			/* The page got truncated from under us */
			f2fs_put_page(page, 1);
			goto repeat;
		}
	}

	f2fs_wait_on_page_writeback(page, DATA, false, true);

	if (len == PAGE_SIZE || PageUptodate(page))
		return 0;

	if (!(pos & (PAGE_SIZE - 1)) && (pos + len) >= i_size_read(inode) &&
	    !f2fs_verity_in_progress(inode)) {
		zero_user_segment(page, len, PAGE_SIZE);
		return 0;
	}

	if (blkaddr == NEW_ADDR) {
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
	} else {
		if (!f2fs_is_valid_blkaddr(sbi, blkaddr,
				DATA_GENERIC_ENHANCE_READ)) {
			err = -EFSCORRUPTED;
			goto fail;
		}
		err = f2fs_submit_page_read(inode, page, blkaddr);
		if (err)
			goto fail;

		lock_page(page);
		if (unlikely(page->mapping != mapping)) {
			f2fs_put_page(page, 1);
			goto repeat;
		}
		if (unlikely(!PageUptodate(page))) {
			err = -EIO;
			goto fail;
		}
	}
	return 0;

fail:
	f2fs_put_page(page, 1);
	f2fs_write_failed(mapping, pos + len);
	if (drop_atomic)
		f2fs_drop_inmem_pages_all(sbi, false);
	return err;
}