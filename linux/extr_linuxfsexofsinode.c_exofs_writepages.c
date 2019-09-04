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
struct writeback_control {long range_start; long range_end; scalar_t__ sync_mode; } ;
struct page_collect {unsigned int nr_pages; struct page** pages; } ;
struct page {int dummy; } ;
struct address_space {long nrpages; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,int /*<<< orphan*/ ,long,long,long,long,long,long) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,int) ; 
 long LLONG_MAX ; 
 long PAGE_SHIFT ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  _pcol_init (struct page_collect*,long,TYPE_1__*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct page_collect*) ; 
 int write_exec (struct page_collect*) ; 
 int /*<<< orphan*/  writepage_strip ; 

__attribute__((used)) static int exofs_writepages(struct address_space *mapping,
		       struct writeback_control *wbc)
{
	struct page_collect pcol;
	long start, end, expected_pages;
	int ret;

	start = wbc->range_start >> PAGE_SHIFT;
	end = (wbc->range_end == LLONG_MAX) ?
			start + mapping->nrpages :
			wbc->range_end >> PAGE_SHIFT;

	if (start || end)
		expected_pages = end - start + 1;
	else
		expected_pages = mapping->nrpages;

	if (expected_pages < 32L)
		expected_pages = 32L;

	EXOFS_DBGMSG2("inode(0x%lx) wbc->start=0x%llx wbc->end=0x%llx "
		     "nrpages=%lu start=0x%lx end=0x%lx expected_pages=%ld\n",
		     mapping->host->i_ino, wbc->range_start, wbc->range_end,
		     mapping->nrpages, start, end, expected_pages);

	_pcol_init(&pcol, expected_pages, mapping->host);

	ret = write_cache_pages(mapping, wbc, writepage_strip, &pcol);
	if (unlikely(ret)) {
		EXOFS_ERR("write_cache_pages => %d\n", ret);
		return ret;
	}

	ret = write_exec(&pcol);
	if (unlikely(ret))
		return ret;

	if (wbc->sync_mode == WB_SYNC_ALL) {
		return write_exec(&pcol); /* pump the last reminder */
	} else if (pcol.nr_pages) {
		/* not SYNC let the reminder join the next writeout */
		unsigned i;

		for (i = 0; i < pcol.nr_pages; i++) {
			struct page *page = pcol.pages[i];

			end_page_writeback(page);
			set_page_dirty(page);
			unlock_page(page);
		}
	}
	return 0;
}