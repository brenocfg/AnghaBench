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
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void btrfs_drop_pages(struct page **pages, size_t num_pages)
{
	size_t i;
	for (i = 0; i < num_pages; i++) {
		/* page checked is some magic around finding pages that
		 * have been modified without going through btrfs_set_page_dirty
		 * clear it here. There should be no need to mark the pages
		 * accessed as prepare_pages should have marked them accessed
		 * in prepare_pages via find_or_create_page()
		 */
		ClearPageChecked(pages[i]);
		unlock_page(pages[i]);
		put_page(pages[i]);
	}
}