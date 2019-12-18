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
struct writeback_control {int range_end; int nr_to_write; } ;
struct page {int /*<<< orphan*/  mapping; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_write_back_from_locked_page (int /*<<< orphan*/ ,struct writeback_control*,struct page*,int) ; 

int afs_writepage(struct page *page, struct writeback_control *wbc)
{
	int ret;

	_enter("{%lx},", page->index);

	ret = afs_write_back_from_locked_page(page->mapping, wbc, page,
					      wbc->range_end >> PAGE_SHIFT);
	if (ret < 0) {
		_leave(" = %d", ret);
		return 0;
	}

	wbc->nr_to_write -= ret;

	_leave(" = 0");
	return 0;
}