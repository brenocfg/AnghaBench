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
struct page {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_dirty_writeback ) (struct page*,int*,int*) ;} ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 int PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  page_has_private (struct page*) ; 
 int /*<<< orphan*/  page_is_file_cache (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*,int*,int*) ; 

__attribute__((used)) static void page_check_dirty_writeback(struct page *page,
				       bool *dirty, bool *writeback)
{
	struct address_space *mapping;

	/*
	 * Anonymous pages are not handled by flushers and must be written
	 * from reclaim context. Do not stall reclaim based on them
	 */
	if (!page_is_file_cache(page) ||
	    (PageAnon(page) && !PageSwapBacked(page))) {
		*dirty = false;
		*writeback = false;
		return;
	}

	/* By default assume that the page flags are accurate */
	*dirty = PageDirty(page);
	*writeback = PageWriteback(page);

	/* Verify dirty/writeback state if the filesystem supports it */
	if (!page_has_private(page))
		return;

	mapping = page_mapping(page);
	if (mapping && mapping->a_ops->is_dirty_writeback)
		mapping->a_ops->is_dirty_writeback(page, dirty, writeback);
}