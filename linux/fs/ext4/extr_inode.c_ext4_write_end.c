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
struct inode {scalar_t__ i_size; scalar_t__ i_nlink; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 unsigned int block_write_end (struct file*,struct address_space*,scalar_t__,unsigned int,unsigned int,struct page*,void*) ; 
 scalar_t__ ext4_can_truncate (struct inode*) ; 
 int ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int ext4_update_inode_size (struct inode*,scalar_t__) ; 
 int ext4_verity_in_progress (struct inode*) ; 
 int ext4_write_inline_data_end (struct inode*,scalar_t__,unsigned int,unsigned int,struct page*) ; 
 int /*<<< orphan*/  pagecache_isize_extended (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_write_end (struct inode*,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ext4_write_end(struct file *file,
			  struct address_space *mapping,
			  loff_t pos, unsigned len, unsigned copied,
			  struct page *page, void *fsdata)
{
	handle_t *handle = ext4_journal_current_handle();
	struct inode *inode = mapping->host;
	loff_t old_size = inode->i_size;
	int ret = 0, ret2;
	int i_size_changed = 0;
	int inline_data = ext4_has_inline_data(inode);
	bool verity = ext4_verity_in_progress(inode);

	trace_ext4_write_end(inode, pos, len, copied);
	if (inline_data) {
		ret = ext4_write_inline_data_end(inode, pos, len,
						 copied, page);
		if (ret < 0) {
			unlock_page(page);
			put_page(page);
			goto errout;
		}
		copied = ret;
	} else
		copied = block_write_end(file, mapping, pos,
					 len, copied, page, fsdata);
	/*
	 * it's important to update i_size while still holding page lock:
	 * page writeout could otherwise come in and zero beyond i_size.
	 *
	 * If FS_IOC_ENABLE_VERITY is running on this inode, then Merkle tree
	 * blocks are being written past EOF, so skip the i_size update.
	 */
	if (!verity)
		i_size_changed = ext4_update_inode_size(inode, pos + copied);
	unlock_page(page);
	put_page(page);

	if (old_size < pos && !verity)
		pagecache_isize_extended(inode, old_size, pos);
	/*
	 * Don't mark the inode dirty under page lock. First, it unnecessarily
	 * makes the holding time of page lock longer. Second, it forces lock
	 * ordering of page lock and transaction start for journaling
	 * filesystems.
	 */
	if (i_size_changed || inline_data)
		ext4_mark_inode_dirty(handle, inode);

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