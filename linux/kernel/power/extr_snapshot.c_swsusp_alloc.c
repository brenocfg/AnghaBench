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
struct memory_bitmap {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PG_ANY ; 
 unsigned int alloc_highmem ; 
 scalar_t__ alloc_highmem_pages (struct memory_bitmap*,unsigned int) ; 
 struct page* alloc_image_page (int /*<<< orphan*/ ) ; 
 unsigned int alloc_normal ; 
 scalar_t__ get_highmem_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_set_bit (struct memory_bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  swsusp_free () ; 

__attribute__((used)) static int swsusp_alloc(struct memory_bitmap *copy_bm,
			unsigned int nr_pages, unsigned int nr_highmem)
{
	if (nr_highmem > 0) {
		if (get_highmem_buffer(PG_ANY))
			goto err_out;
		if (nr_highmem > alloc_highmem) {
			nr_highmem -= alloc_highmem;
			nr_pages += alloc_highmem_pages(copy_bm, nr_highmem);
		}
	}
	if (nr_pages > alloc_normal) {
		nr_pages -= alloc_normal;
		while (nr_pages-- > 0) {
			struct page *page;

			page = alloc_image_page(GFP_ATOMIC);
			if (!page)
				goto err_out;
			memory_bm_set_bit(copy_bm, page_to_pfn(page));
		}
	}

	return 0;

 err_out:
	swsusp_free();
	return -ENOMEM;
}