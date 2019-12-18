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
struct page {int /*<<< orphan*/  mapping; int /*<<< orphan*/  index; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MIGRATEPAGE_SUCCESS ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int page_count (struct page*) ; 
 int page_has_private (struct page*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  page_ref_freeze (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_unfreeze (struct page*,int) ; 
 int /*<<< orphan*/  xas ; 
 struct page* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  xas_unlock_irq (int /*<<< orphan*/ *) ; 

int migrate_huge_page_move_mapping(struct address_space *mapping,
				   struct page *newpage, struct page *page)
{
	XA_STATE(xas, &mapping->i_pages, page_index(page));
	int expected_count;

	xas_lock_irq(&xas);
	expected_count = 2 + page_has_private(page);
	if (page_count(page) != expected_count || xas_load(&xas) != page) {
		xas_unlock_irq(&xas);
		return -EAGAIN;
	}

	if (!page_ref_freeze(page, expected_count)) {
		xas_unlock_irq(&xas);
		return -EAGAIN;
	}

	newpage->index = page->index;
	newpage->mapping = page->mapping;

	get_page(newpage);

	xas_store(&xas, newpage);

	page_ref_unfreeze(page, expected_count - 1);

	xas_unlock_irq(&xas);

	return MIGRATEPAGE_SUCCESS;
}