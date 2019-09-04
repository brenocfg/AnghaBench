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
 int /*<<< orphan*/  v9fs_fscache_invalidate_page (struct page*) ; 

__attribute__((used)) static void v9fs_invalidate_page(struct page *page, unsigned int offset,
				 unsigned int length)
{
	/*
	 * If called with zero offset, we should release
	 * the private state assocated with the page
	 */
	if (offset == 0 && length == PAGE_SIZE)
		v9fs_fscache_invalidate_page(page);
}