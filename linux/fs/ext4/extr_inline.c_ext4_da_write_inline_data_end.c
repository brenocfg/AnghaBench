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
struct inode {scalar_t__ i_size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int ext4_write_inline_data_end (struct inode*,scalar_t__,unsigned int,unsigned int,struct page*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int ext4_da_write_inline_data_end(struct inode *inode, loff_t pos,
				  unsigned len, unsigned copied,
				  struct page *page)
{
	int ret;

	ret = ext4_write_inline_data_end(inode, pos, len, copied, page);
	if (ret < 0) {
		unlock_page(page);
		put_page(page);
		return ret;
	}
	copied = ret;

	/*
	 * No need to use i_size_read() here, the i_size
	 * cannot change under us because we hold i_mutex.
	 *
	 * But it's important to update i_size while still holding page lock:
	 * page writeout could otherwise come in and zero beyond i_size.
	 */
	if (pos+copied > inode->i_size)
		i_size_write(inode, pos+copied);
	unlock_page(page);
	put_page(page);

	/*
	 * Don't mark the inode dirty under page lock. First, it unnecessarily
	 * makes the holding time of page lock longer. Second, it forces lock
	 * ordering of page lock and transaction start for journaling
	 * filesystems.
	 */
	mark_inode_dirty(inode);

	return copied;
}