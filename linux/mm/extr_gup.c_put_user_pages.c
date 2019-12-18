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
 int /*<<< orphan*/  put_user_page (struct page*) ; 

void put_user_pages(struct page **pages, unsigned long npages)
{
	unsigned long index;

	/*
	 * TODO: this can be optimized for huge pages: if a series of pages is
	 * physically contiguous and part of the same compound page, then a
	 * single operation to the head page should suffice.
	 */
	for (index = 0; index < npages; index++)
		put_user_page(pages[index]);
}