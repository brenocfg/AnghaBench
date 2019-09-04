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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_write_end(struct file *file, struct address_space *mapping,
		loff_t pos, unsigned len, unsigned copied,
		struct page *page, void *fsdata)
{
	struct inode *inode = page->mapping->host;

	/* Haven't copied anything?  Skip zeroing, size extending, dirtying. */
	if (!copied)
		goto unlock;

	if (!PageUptodate(page)) {
		/* Zero any unwritten bytes at the end of the page */
		size_t endoff = (pos + copied) & ~PAGE_MASK;
		if (endoff)
			zero_user_segment(page, endoff, PAGE_SIZE);
		SetPageUptodate(page);
	}

	fuse_write_update_size(inode, pos + copied);
	set_page_dirty(page);

unlock:
	unlock_page(page);
	put_page(page);

	return copied;
}