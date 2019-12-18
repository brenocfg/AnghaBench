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

int noop_set_page_dirty(struct page *page)
{
	/*
	 * Unlike __set_page_dirty_no_writeback that handles dirty page
	 * tracking in the page object, dax does all dirty tracking in
	 * the inode address_space in response to mkwrite faults. In the
	 * dax case we only need to worry about potentially dirty CPU
	 * caches, not dirty page cache pages to write back.
	 *
	 * This callback is defined to prevent fallback to
	 * __set_page_dirty_buffers() in set_page_dirty().
	 */
	return 0;
}