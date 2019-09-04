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
typedef  scalar_t__ u64 ;
struct page {int /*<<< orphan*/  index; int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  add_to_page_cache_lru (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 struct page* lru_to_page (struct list_head*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static struct page *
iomap_next_page(struct inode *inode, struct list_head *pages, loff_t pos,
		loff_t length, loff_t *done)
{
	while (!list_empty(pages)) {
		struct page *page = lru_to_page(pages);

		if (page_offset(page) >= (u64)pos + length)
			break;

		list_del(&page->lru);
		if (!add_to_page_cache_lru(page, inode->i_mapping, page->index,
				GFP_NOFS))
			return page;

		/*
		 * If we already have a page in the page cache at index we are
		 * done.  Upper layers don't care if it is uptodate after the
		 * readpages call itself as every page gets checked again once
		 * actually needed.
		 */
		*done += PAGE_SIZE;
		put_page(page);
	}

	return NULL;
}