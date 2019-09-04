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
struct page {int /*<<< orphan*/  index; } ;
struct address_space {int dummy; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*) ; 
 int /*<<< orphan*/  do_invalidatepage (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_has_private (struct page*) ; 
 scalar_t__ page_mapped (struct page*) ; 
 int /*<<< orphan*/  unmap_mapping_pages (struct address_space*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
truncate_cleanup_page(struct address_space *mapping, struct page *page)
{
	if (page_mapped(page)) {
		pgoff_t nr = PageTransHuge(page) ? HPAGE_PMD_NR : 1;
		unmap_mapping_pages(mapping, page->index, nr, false);
	}

	if (page_has_private(page))
		do_invalidatepage(page, 0, PAGE_SIZE);

	/*
	 * Some filesystems seem to re-dirty the page even after
	 * the VM has canceled the dirty bit (eg ext3 journaling).
	 * Hence dirty accounting check is placed after invalidation.
	 */
	cancel_dirty_page(page);
	ClearPageMappedToDisk(page);
}