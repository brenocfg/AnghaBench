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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mapping; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int i_blocksize (struct inode*) ; 
 scalar_t__ page_mkclean (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ round_up (scalar_t__,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void pagecache_isize_extended(struct inode *inode, loff_t from, loff_t to)
{
	int bsize = i_blocksize(inode);
	loff_t rounded_from;
	struct page *page;
	pgoff_t index;

	WARN_ON(to > inode->i_size);

	if (from >= to || bsize == PAGE_SIZE)
		return;
	/* Page straddling @from will not have any hole block created? */
	rounded_from = round_up(from, bsize);
	if (to <= rounded_from || !(rounded_from & (PAGE_SIZE - 1)))
		return;

	index = from >> PAGE_SHIFT;
	page = find_lock_page(inode->i_mapping, index);
	/* Page not cached? Nothing to do */
	if (!page)
		return;
	/*
	 * See clear_page_dirty_for_io() for details why set_page_dirty()
	 * is needed.
	 */
	if (page_mkclean(page))
		set_page_dirty(page);
	unlock_page(page);
	put_page(page);
}