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
struct address_space {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  delete_from_page_cache (struct page*) ; 
 int /*<<< orphan*/  truncate_cleanup_page (struct address_space*,struct page*) ; 

int truncate_inode_page(struct address_space *mapping, struct page *page)
{
	VM_BUG_ON_PAGE(PageTail(page), page);

	if (page->mapping != mapping)
		return -EIO;

	truncate_cleanup_page(mapping, page);
	delete_from_page_cache(page);
	return 0;
}