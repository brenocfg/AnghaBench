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
struct inode {unsigned int i_size; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  _write_failed (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int exofs_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	loff_t last_pos = pos + copied;

	if (!PageUptodate(page)) {
		if (copied < len) {
			_write_failed(inode, pos + len);
			copied = 0;
			goto out;
		}
		SetPageUptodate(page);
	}
	if (last_pos > inode->i_size) {
		i_size_write(inode, last_pos);
		mark_inode_dirty(inode);
	}
	set_page_dirty(page);
out:
	unlock_page(page);
	put_page(page);
	return copied;
}