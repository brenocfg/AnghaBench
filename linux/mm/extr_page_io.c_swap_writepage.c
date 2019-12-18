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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int __swap_writepage (struct page*,struct writeback_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  end_swap_bio_write ; 
 scalar_t__ frontswap_store (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 scalar_t__ try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int swap_writepage(struct page *page, struct writeback_control *wbc)
{
	int ret = 0;

	if (try_to_free_swap(page)) {
		unlock_page(page);
		goto out;
	}
	if (frontswap_store(page) == 0) {
		set_page_writeback(page);
		unlock_page(page);
		end_page_writeback(page);
		goto out;
	}
	ret = __swap_writepage(page, wbc, end_swap_bio_write);
out:
	return ret;
}