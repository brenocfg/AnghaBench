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
struct writeback_control {int /*<<< orphan*/  pages_skipped; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  account_page_redirty (struct page*) ; 

int redirty_page_for_writepage(struct writeback_control *wbc, struct page *page)
{
	int ret;

	wbc->pages_skipped++;
	ret = __set_page_dirty_nobuffers(page);
	account_page_redirty(page);
	return ret;
}