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
struct buffer_head {struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  attach_nobh_buffers (struct page*,struct buffer_head*) ; 
 int /*<<< orphan*/  free_buffer_head (struct buffer_head*) ; 
 int generic_write_end (struct file*,struct address_space*,unsigned int,unsigned int,unsigned int,struct page*,void*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nobh_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *head = fsdata;
	struct buffer_head *bh;
	BUG_ON(fsdata != NULL && page_has_buffers(page));

	if (unlikely(copied < len) && head)
		attach_nobh_buffers(page, head);
	if (page_has_buffers(page))
		return generic_write_end(file, mapping, pos, len,
					copied, page, fsdata);

	SetPageUptodate(page);
	set_page_dirty(page);
	if (pos+copied > inode->i_size) {
		i_size_write(inode, pos+copied);
		mark_inode_dirty(inode);
	}

	unlock_page(page);
	put_page(page);

	while (head) {
		bh = head;
		head = head->b_this_page;
		free_buffer_head(bh);
	}

	return copied;
}