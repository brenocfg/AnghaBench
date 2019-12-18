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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_nlink; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 unsigned int AOP_FLAG_NOFS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_WRITE_PAGE ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int __block_write_begin (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_commit_write (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_destroy_inline_data_nolock (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_get_block ; 
 int /*<<< orphan*/  ext4_get_block_unwritten ; 
 unsigned int ext4_get_inline_size (struct inode*) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_read_inline_page (struct inode*,struct page*) ; 
 scalar_t__ ext4_should_dioread_nolock (struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int ext4_walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ext4_convert_inline_data_to_extent(struct address_space *mapping,
					      struct inode *inode,
					      unsigned flags)
{
	int ret, needed_blocks, no_expand;
	handle_t *handle = NULL;
	int retries = 0, sem_held = 0;
	struct page *page = NULL;
	unsigned from, to;
	struct ext4_iloc iloc;

	if (!ext4_has_inline_data(inode)) {
		/*
		 * clear the flag so that no new write
		 * will trap here again.
		 */
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		return 0;
	}

	needed_blocks = ext4_writepage_trans_blocks(inode);

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret)
		return ret;

retry:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		handle = NULL;
		goto out;
	}

	/* We cannot recurse into the filesystem as the transaction is already
	 * started */
	flags |= AOP_FLAG_NOFS;

	page = grab_cache_page_write_begin(mapping, 0, flags);
	if (!page) {
		ret = -ENOMEM;
		goto out;
	}

	ext4_write_lock_xattr(inode, &no_expand);
	sem_held = 1;
	/* If some one has already done this for us, just exit. */
	if (!ext4_has_inline_data(inode)) {
		ret = 0;
		goto out;
	}

	from = 0;
	to = ext4_get_inline_size(inode);
	if (!PageUptodate(page)) {
		ret = ext4_read_inline_page(inode, page);
		if (ret < 0)
			goto out;
	}

	ret = ext4_destroy_inline_data_nolock(handle, inode);
	if (ret)
		goto out;

	if (ext4_should_dioread_nolock(inode)) {
		ret = __block_write_begin(page, from, to,
					  ext4_get_block_unwritten);
	} else
		ret = __block_write_begin(page, from, to, ext4_get_block);

	if (!ret && ext4_should_journal_data(inode)) {
		ret = ext4_walk_page_buffers(handle, page_buffers(page),
					     from, to, NULL,
					     do_journal_get_write_access);
	}

	if (ret) {
		unlock_page(page);
		put_page(page);
		page = NULL;
		ext4_orphan_add(handle, inode);
		ext4_write_unlock_xattr(inode, &no_expand);
		sem_held = 0;
		ext4_journal_stop(handle);
		handle = NULL;
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

	if (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		goto retry;

	if (page)
		block_commit_write(page, from, to);
out:
	if (page) {
		unlock_page(page);
		put_page(page);
	}
	if (sem_held)
		ext4_write_unlock_xattr(inode, &no_expand);
	if (handle)
		ext4_journal_stop(handle);
	brelse(iloc.bh);
	return ret;
}