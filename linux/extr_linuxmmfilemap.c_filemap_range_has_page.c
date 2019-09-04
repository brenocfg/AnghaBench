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
struct address_space {scalar_t__ nrpages; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  find_get_pages_range (struct address_space*,int*,int,int,struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

bool filemap_range_has_page(struct address_space *mapping,
			   loff_t start_byte, loff_t end_byte)
{
	pgoff_t index = start_byte >> PAGE_SHIFT;
	pgoff_t end = end_byte >> PAGE_SHIFT;
	struct page *page;

	if (end_byte < start_byte)
		return false;

	if (mapping->nrpages == 0)
		return false;

	if (!find_get_pages_range(mapping, &index, end, 1, &page))
		return false;
	put_page(page);
	return true;
}