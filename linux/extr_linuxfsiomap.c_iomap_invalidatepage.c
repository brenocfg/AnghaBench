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

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*) ; 
 int /*<<< orphan*/  iomap_page_release (struct page*) ; 

void
iomap_invalidatepage(struct page *page, unsigned int offset, unsigned int len)
{
	/*
	 * If we are invalidating the entire page, clear the dirty state from it
	 * and release it to avoid unnecessary buildup of the LRU.
	 */
	if (offset == 0 && len == PAGE_SIZE) {
		WARN_ON_ONCE(PageWriteback(page));
		cancel_dirty_page(page);
		iomap_page_release(page);
	}
}