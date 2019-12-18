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
struct inode {int i_size; int /*<<< orphan*/  i_sb; scalar_t__ i_nlink; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_WRITE_PAGE ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __block_write_begin (struct page*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 int ext4_block_write_begin (struct page*,int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_can_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_get_block ; 
 int /*<<< orphan*/  ext4_get_block_unwritten ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_dioread_nolock (struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int ext4_try_to_write_inline_data (struct address_space*,struct inode*,int,unsigned int,unsigned int,struct page**) ; 
 int /*<<< orphan*/  ext4_verity_in_progress (struct inode*) ; 
 int ext4_walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_write_begin (struct inode*,int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

__attribute__((used)) static int ext4_write_begin(struct file *file, struct address_space *mapping,
			    loff_t pos, unsigned len, unsigned flags,
			    struct page **pagep, void **fsdata)
{
	struct inode *inode = mapping->host;
	int ret, needed_blocks;
	handle_t *handle;
	int retries = 0;
	struct page *page;
	pgoff_t index;
	unsigned from, to;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	trace_ext4_write_begin(inode, pos, len, flags);
	/*
	 * Reserve one block more for addition to orphan list in case
	 * we allocate blocks but write fails for some reason
	 */
	needed_blocks = ext4_writepage_trans_blocks(inode) + 1;
	index = pos >> PAGE_SHIFT;
	from = pos & (PAGE_SIZE - 1);
	to = from + len;

	if (ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA)) {
		ret = ext4_try_to_write_inline_data(mapping, inode, pos, len,
						    flags, pagep);
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

retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
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
	if (ext4_should_dioread_nolock(inode))
		ret = ext4_block_write_begin(page, pos, len,
					     ext4_get_block_unwritten);
	else
		ret = ext4_block_write_begin(page, pos, len,
					     ext4_get_block);
#else
	if (ext4_should_dioread_nolock(inode))
		ret = __block_write_begin(page, pos, len,
					  ext4_get_block_unwritten);
	else
		ret = __block_write_begin(page, pos, len, ext4_get_block);
#endif
	if (!ret && ext4_should_journal_data(inode)) {
		ret = ext4_walk_page_buffers(handle, page_buffers(page),
					     from, to, NULL,
					     do_journal_get_write_access);
	}

	if (ret) {
		bool extended = (pos + len > inode->i_size) &&
				!ext4_verity_in_progress(inode);

		unlock_page(page);
		/*
		 * __block_write_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_read because we hold i_mutex.
		 *
		 * Add inode to orphan list in case we crash before
		 * truncate finishes
		 */
		if (extended && ext4_can_truncate(inode))
			ext4_orphan_add(handle, inode);

		ext4_journal_stop(handle);
		if (extended) {
			ext4_truncate_failed_write(inode);
			/*
			 * If truncate failed early the inode might
			 * still be on the orphan list; we need to
			 * make sure the inode is removed from the
			 * orphan list in that case.
			 */
			if (inode->i_nlink)
				ext4_orphan_del(NULL, inode);
		}

		if (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			goto retry_journal;
		put_page(page);
		return ret;
	}
	*pagep = page;
	return ret;
}