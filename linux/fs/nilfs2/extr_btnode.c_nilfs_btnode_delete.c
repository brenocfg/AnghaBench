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
struct page {struct address_space* mapping; } ;
struct buffer_head {struct page* b_page; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int PageDirty (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  invalidate_inode_pages2_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_forget_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

void nilfs_btnode_delete(struct buffer_head *bh)
{
	struct address_space *mapping;
	struct page *page = bh->b_page;
	pgoff_t index = page_index(page);
	int still_dirty;

	get_page(page);
	lock_page(page);
	wait_on_page_writeback(page);

	nilfs_forget_buffer(bh);
	still_dirty = PageDirty(page);
	mapping = page->mapping;
	unlock_page(page);
	put_page(page);

	if (!still_dirty && mapping)
		invalidate_inode_pages2_range(mapping, index, index);
}