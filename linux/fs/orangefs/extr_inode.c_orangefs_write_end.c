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
struct page {TYPE_1__* mapping; } ;
struct inode {unsigned int i_size; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (int /*<<< orphan*/ ) ; 
 unsigned int page_offset (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 

__attribute__((used)) static int orangefs_write_end(struct file *file, struct address_space *mapping,
    loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
{
	struct inode *inode = page->mapping->host;
	loff_t last_pos = pos + copied;

	/*
	 * No need to use i_size_read() here, the i_size
	 * cannot change under us because we hold the i_mutex.
	 */
	if (last_pos > inode->i_size)
		i_size_write(inode, last_pos);

	/* zero the stale part of the page if we did a short copy */
	if (!PageUptodate(page)) {
		unsigned from = pos & (PAGE_SIZE - 1);
		if (copied < len) {
			zero_user(page, from + copied, len - copied);
		}
		/* Set fully written pages uptodate. */
		if (pos == page_offset(page) &&
		    (len == PAGE_SIZE || pos + len == inode->i_size)) {
			zero_user_segment(page, from + copied, PAGE_SIZE);
			SetPageUptodate(page);
		}
	}

	set_page_dirty(page);
	unlock_page(page);
	put_page(page);

	mark_inode_dirty_sync(file_inode(file));
	return copied;
}