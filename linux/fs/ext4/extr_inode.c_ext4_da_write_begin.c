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
struct inode {unsigned int i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  unsigned int pgoff_t ;
typedef  unsigned int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_WRITE_PAGE ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 scalar_t__ FALL_BACK_TO_NONDELALLOC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 unsigned int PAGE_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int __block_write_begin (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int ext4_block_write_begin (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_da_get_block_prep ; 
 int /*<<< orphan*/  ext4_da_write_credits (struct inode*,unsigned int,unsigned int) ; 
 int ext4_da_write_inline_data_begin (struct address_space*,struct inode*,unsigned int,unsigned int,unsigned int,struct page**,void**) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_nonda_switch (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 scalar_t__ ext4_verity_in_progress (struct inode*) ; 
 int ext4_write_begin (struct file*,struct address_space*,unsigned int,unsigned int,unsigned int,struct page**,void**) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_da_write_begin (struct inode*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

__attribute__((used)) static int ext4_da_write_begin(struct file *file, struct address_space *mapping,
			       loff_t pos, unsigned len, unsigned flags,
			       struct page **pagep, void **fsdata)
{
	int ret, retries = 0;
	struct page *page;
	pgoff_t index;
	struct inode *inode = mapping->host;
	handle_t *handle;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	index = pos >> PAGE_SHIFT;

	if (ext4_nonda_switch(inode->i_sb) || S_ISLNK(inode->i_mode) ||
	    ext4_verity_in_progress(inode)) {
		*fsdata = (void *)FALL_BACK_TO_NONDELALLOC;
		return ext4_write_begin(file, mapping, pos,
					len, flags, pagep, fsdata);
	}
	*fsdata = (void *)0;
	trace_ext4_da_write_begin(inode, pos, len, flags);

	if (ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA)) {
		ret = ext4_da_write_inline_data_begin(mapping, inode,
						      pos, len, flags,
						      pagep, fsdata);
		if (ret < 0)
			return ret;
		if (ret == 1)
			return 0;
	}

	/*
	 * grab_cache_page_write_begin() can take a long time if the
	 * system is thrashing due to memory pressure, or if the page
	 * is being written back.  So grab it first before we start
	 * the transaction handle.  This also allows us to allocate
	 * the page (if needed) without using GFP_NOFS.
	 */
retry_grab:
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	unlock_page(page);

	/*
	 * With delayed allocation, we don't log the i_disksize update
	 * if there is delayed block allocation. But we still need
	 * to journalling the i_disksize update if writes to the end
	 * of file which has an already mapped buffer.
	 */
retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE,
				ext4_da_write_credits(inode, pos, len));
	if (IS_ERR(handle)) {
		put_page(page);
		return PTR_ERR(handle);
	}

	lock_page(page);
	if (page->mapping != mapping) {
		/* The page got truncated from under us */
		unlock_page(page);
		put_page(page);
		ext4_journal_stop(handle);
		goto retry_grab;
	}
	/* In case writeback began while the page was unlocked */
	wait_for_stable_page(page);

#ifdef CONFIG_FS_ENCRYPTION
	ret = ext4_block_write_begin(page, pos, len,
				     ext4_da_get_block_prep);
#else
	ret = __block_write_begin(page, pos, len, ext4_da_get_block_prep);
#endif
	if (ret < 0) {
		unlock_page(page);
		ext4_journal_stop(handle);
		/*
		 * block_write_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_read because we hold i_mutex.
		 */
		if (pos + len > inode->i_size)
			ext4_truncate_failed_write(inode);

		if (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			goto retry_journal;

		put_page(page);
		return ret;
	}

	*pagep = page;
	return ret;
}