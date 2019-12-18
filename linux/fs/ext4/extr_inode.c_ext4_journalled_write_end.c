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
struct page {int dummy; } ;
struct inode {int i_size; scalar_t__ i_nlink; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
struct TYPE_13__ {TYPE_1__* h_transaction; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_12__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_datasync_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_10__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_JDATA ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ ext4_can_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_valid (TYPE_2__*) ; 
 int ext4_has_inline_data (struct inode*) ; 
 TYPE_2__* ext4_journal_current_handle () ; 
 int ext4_journal_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  ext4_journalled_zero_new_buffers (TYPE_2__*,struct page*,unsigned int,unsigned int) ; 
 int ext4_mark_inode_dirty (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_add (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int ext4_update_inode_size (struct inode*,int) ; 
 int ext4_verity_in_progress (struct inode*) ; 
 int ext4_walk_page_buffers (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,unsigned int,int*,int /*<<< orphan*/ ) ; 
 int ext4_write_inline_data_end (struct inode*,int,unsigned int,unsigned int,struct page*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  pagecache_isize_extended (struct inode*,int,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_journalled_write_end (struct inode*,int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  write_end_fn ; 

__attribute__((used)) static int ext4_journalled_write_end(struct file *file,
				     struct address_space *mapping,
				     loff_t pos, unsigned len, unsigned copied,
				     struct page *page, void *fsdata)
{
	handle_t *handle = ext4_journal_current_handle();
	struct inode *inode = mapping->host;
	loff_t old_size = inode->i_size;
	int ret = 0, ret2;
	int partial = 0;
	unsigned from, to;
	int size_changed = 0;
	int inline_data = ext4_has_inline_data(inode);
	bool verity = ext4_verity_in_progress(inode);

	trace_ext4_journalled_write_end(inode, pos, len, copied);
	from = pos & (PAGE_SIZE - 1);
	to = from + len;

	BUG_ON(!ext4_handle_valid(handle));

	if (inline_data) {
		ret = ext4_write_inline_data_end(inode, pos, len,
						 copied, page);
		if (ret < 0) {
			unlock_page(page);
			put_page(page);
			goto errout;
		}
		copied = ret;
	} else if (unlikely(copied < len) && !PageUptodate(page)) {
		copied = 0;
		ext4_journalled_zero_new_buffers(handle, page, from, to);
	} else {
		if (unlikely(copied < len))
			ext4_journalled_zero_new_buffers(handle, page,
							 from + copied, to);
		ret = ext4_walk_page_buffers(handle, page_buffers(page), from,
					     from + copied, &partial,
					     write_end_fn);
		if (!partial)
			SetPageUptodate(page);
	}
	if (!verity)
		size_changed = ext4_update_inode_size(inode, pos + copied);
	ext4_set_inode_state(inode, EXT4_STATE_JDATA);
	EXT4_I(inode)->i_datasync_tid = handle->h_transaction->t_tid;
	unlock_page(page);
	put_page(page);

	if (old_size < pos && !verity)
		pagecache_isize_extended(inode, old_size, pos);

	if (size_changed || inline_data) {
		ret2 = ext4_mark_inode_dirty(handle, inode);
		if (!ret)
			ret = ret2;
	}

	if (pos + len > inode->i_size && !verity && ext4_can_truncate(inode))
		/* if we have allocated more blocks and copied
		 * less. We will have blocks allocated outside
		 * inode->i_size. So truncate them
		 */
		ext4_orphan_add(handle, inode);

errout:
	ret2 = ext4_journal_stop(handle);
	if (!ret)
		ret = ret2;
	if (pos + len > inode->i_size && !verity) {
		ext4_truncate_failed_write(inode);
		/*
		 * If truncate failed early the inode might still be
		 * on the orphan list; we need to make sure the inode
		 * is removed from the orphan list in that case.
		 */
		if (inode->i_nlink)
			ext4_orphan_del(NULL, inode);
	}

	return ret ? ret : copied;
}