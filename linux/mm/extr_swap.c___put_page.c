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
struct page {int /*<<< orphan*/  pgmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  __put_compound_page (struct page*) ; 
 int /*<<< orphan*/  __put_single_page (struct page*) ; 
 scalar_t__ is_zone_device_page (struct page*) ; 
 int /*<<< orphan*/  put_dev_pagemap (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __put_page(struct page *page)
{
	if (is_zone_device_page(page)) {
		put_dev_pagemap(page->pgmap);

		/*
		 * The page belongs to the device that created pgmap. Do
		 * not return it to page allocator.
		 */
		return;
	}

	if (unlikely(PageCompound(page)))
		__put_compound_page(page);
	else
		__put_single_page(page);
}