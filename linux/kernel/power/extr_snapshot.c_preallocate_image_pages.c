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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  alloc_highmem ; 
 struct page* alloc_image_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_normal ; 
 int /*<<< orphan*/  copy_bm ; 
 int /*<<< orphan*/  memory_bm_set_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

__attribute__((used)) static unsigned long preallocate_image_pages(unsigned long nr_pages, gfp_t mask)
{
	unsigned long nr_alloc = 0;

	while (nr_pages > 0) {
		struct page *page;

		page = alloc_image_page(mask);
		if (!page)
			break;
		memory_bm_set_bit(&copy_bm, page_to_pfn(page));
		if (PageHighMem(page))
			alloc_highmem++;
		else
			alloc_normal++;
		nr_pages--;
		nr_alloc++;
	}

	return nr_alloc;
}