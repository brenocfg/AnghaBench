#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int i_disksize; } ;

/* Variables and functions */
 int CONVERT_INLINE_DATA ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 int FALL_BACK_TO_NONDELALLOC ; 
 int PAGE_SIZE ; 
 scalar_t__ ext4_da_should_update_i_disksize (struct page*,unsigned long) ; 
 int ext4_da_write_inline_data_end (struct inode*,int,unsigned int,unsigned int,struct page*) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_i_disksize (struct inode*,int) ; 
 int ext4_write_end (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page*,void*) ; 
 int generic_write_end (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page*,void*) ; 
 int /*<<< orphan*/  trace_ext4_da_write_end (struct inode*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ext4_da_write_end(struct file *file,
			     struct address_space *mapping,
			     loff_t pos, unsigned len, unsigned copied,
			     struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	int ret = 0, ret2;
	handle_t *handle = ext4_journal_current_handle();
	loff_t new_i_size;
	unsigned long start, end;
	int write_mode = (int)(unsigned long)fsdata;

	if (write_mode == FALL_BACK_TO_NONDELALLOC)
		return ext4_write_end(file, mapping, pos,
				      len, copied, page, fsdata);

	trace_ext4_da_write_end(inode, pos, len, copied);
	start = pos & (PAGE_SIZE - 1);
	end = start + copied - 1;

	/*
	 * generic_write_end() will run mark_inode_dirty() if i_size
	 * changes.  So let's piggyback the i_disksize mark_inode_dirty
	 * into that.
	 */
	new_i_size = pos + copied;
	if (copied && new_i_size > EXT4_I(inode)->i_disksize) {
		if (ext4_has_inline_data(inode) ||
		    ext4_da_should_update_i_disksize(page, end)) {
			ext4_update_i_disksize(inode, new_i_size);
			/* We need to mark inode dirty even if
			 * new_i_size is less that inode->i_size
			 * bu greater than i_disksize.(hint delalloc)
			 */
			ext4_mark_inode_dirty(handle, inode);
		}
	}

	if (write_mode != CONVERT_INLINE_DATA &&
	    ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA) &&
	    ext4_has_inline_data(inode))
		ret2 = ext4_da_write_inline_data_end(inode, pos, len, copied,
						     page);
	else
		ret2 = generic_write_end(file, mapping, pos, len, copied,
							page, fsdata);

	copied = ret2;
	if (ret2 < 0)
		ret = ret2;
	ret2 = ext4_journal_stop(handle);
	if (!ret)
		ret = ret2;

	return ret ? ret : copied;
}