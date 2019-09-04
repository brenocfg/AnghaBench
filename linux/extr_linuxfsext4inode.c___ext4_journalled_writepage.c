#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct page {scalar_t__ index; struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_13__ {TYPE_1__* h_transaction; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_12__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_datasync_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  EXT4_HT_WRITE_PAGE ; 
 TYPE_10__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_JDATA ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  bget_one ; 
 int /*<<< orphan*/  bput_one ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 unsigned int ext4_get_max_inline_size (struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_valid (TYPE_2__*) ; 
 int ext4_has_inline_data (struct inode*) ; 
 TYPE_2__* ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_journal_stop (TYPE_2__*) ; 
 struct buffer_head* ext4_journalled_write_inline_data (struct inode*,unsigned int,struct page*) ; 
 int ext4_mark_inode_dirty (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_walk_page_buffers (TYPE_2__*,struct buffer_head*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_writepage_trans_blocks (struct inode*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  write_end_fn ; 

__attribute__((used)) static int __ext4_journalled_writepage(struct page *page,
				       unsigned int len)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = mapping->host;
	struct buffer_head *page_bufs = NULL;
	handle_t *handle = NULL;
	int ret = 0, err = 0;
	int inline_data = ext4_has_inline_data(inode);
	struct buffer_head *inode_bh = NULL;

	ClearPageChecked(page);

	if (inline_data) {
		BUG_ON(page->index != 0);
		BUG_ON(len > ext4_get_max_inline_size(inode));
		inode_bh = ext4_journalled_write_inline_data(inode, len, page);
		if (inode_bh == NULL)
			goto out;
	} else {
		page_bufs = page_buffers(page);
		if (!page_bufs) {
			BUG();
			goto out;
		}
		ext4_walk_page_buffers(handle, page_bufs, 0, len,
				       NULL, bget_one);
	}
	/*
	 * We need to release the page lock before we start the
	 * journal, so grab a reference so the page won't disappear
	 * out from under us.
	 */
	get_page(page);
	unlock_page(page);

	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE,
				    ext4_writepage_trans_blocks(inode));
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		put_page(page);
		goto out_no_pagelock;
	}
	BUG_ON(!ext4_handle_valid(handle));

	lock_page(page);
	put_page(page);
	if (page->mapping != mapping) {
		/* The page got truncated from under us */
		ext4_journal_stop(handle);
		ret = 0;
		goto out;
	}

	if (inline_data) {
		ret = ext4_mark_inode_dirty(handle, inode);
	} else {
		ret = ext4_walk_page_buffers(handle, page_bufs, 0, len, NULL,
					     do_journal_get_write_access);

		err = ext4_walk_page_buffers(handle, page_bufs, 0, len, NULL,
					     write_end_fn);
	}
	if (ret == 0)
		ret = err;
	EXT4_I(inode)->i_datasync_tid = handle->h_transaction->t_tid;
	err = ext4_journal_stop(handle);
	if (!ret)
		ret = err;

	if (!ext4_has_inline_data(inode))
		ext4_walk_page_buffers(NULL, page_bufs, 0, len,
				       NULL, bput_one);
	ext4_set_inode_state(inode, EXT4_STATE_JDATA);
out:
	unlock_page(page);
out_no_pagelock:
	brelse(inode_bh);
	return ret;
}