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
struct page {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int PAGE_WAS_NOT_IN_IO ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_write_page(struct page *page, int ret)
{
	if (unlikely(ret == PAGE_WAS_NOT_IN_IO))
		return; /* don't pass start don't collect $200 */

	if (ret) {
		mapping_set_error(page->mapping, ret);
		SetPageError(page);
	}
	end_page_writeback(page);
}