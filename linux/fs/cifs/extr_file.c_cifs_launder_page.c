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
struct writeback_control {scalar_t__ range_end; scalar_t__ range_start; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct page {TYPE_1__* mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct page*) ; 
 int /*<<< orphan*/  cifs_fscache_invalidate_page (struct page*,int /*<<< orphan*/ ) ; 
 int cifs_writepage_locked (struct page*,struct writeback_control*) ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 

__attribute__((used)) static int cifs_launder_page(struct page *page)
{
	int rc = 0;
	loff_t range_start = page_offset(page);
	loff_t range_end = range_start + (loff_t)(PAGE_SIZE - 1);
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = 0,
		.range_start = range_start,
		.range_end = range_end,
	};

	cifs_dbg(FYI, "Launder page: %p\n", page);

	if (clear_page_dirty_for_io(page))
		rc = cifs_writepage_locked(page, &wbc);

	cifs_fscache_invalidate_page(page, page->mapping->host);
	return rc;
}