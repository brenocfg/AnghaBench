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
struct address_space {int dummy; } ;

/* Variables and functions */
 scalar_t__ hpage_nr_pages (struct page*) ; 
 scalar_t__ is_device_private_page (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 

__attribute__((used)) static int expected_page_refs(struct address_space *mapping, struct page *page)
{
	int expected_count = 1;

	/*
	 * Device public or private pages have an extra refcount as they are
	 * ZONE_DEVICE pages.
	 */
	expected_count += is_device_private_page(page);
	if (mapping)
		expected_count += hpage_nr_pages(page) + page_has_private(page);

	return expected_count;
}