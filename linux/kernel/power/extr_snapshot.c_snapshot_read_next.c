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
struct swsusp_info {int dummy; } ;
struct snapshot_handle {scalar_t__ cur; void* buffer; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PG_ANY ; 
 scalar_t__ PageHighMem (struct page*) ; 
 void* buffer ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  copy_bm ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 void* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_header (struct swsusp_info*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memory_bm_next_pfn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ nr_copy_pages ; 
 scalar_t__ nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 
 int /*<<< orphan*/  pack_pfns (void*,int /*<<< orphan*/ *) ; 
 void* page_address (struct page*) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 

int snapshot_read_next(struct snapshot_handle *handle)
{
	if (handle->cur > nr_meta_pages + nr_copy_pages)
		return 0;

	if (!buffer) {
		/* This makes the buffer be freed by swsusp_free() */
		buffer = get_image_page(GFP_ATOMIC, PG_ANY);
		if (!buffer)
			return -ENOMEM;
	}
	if (!handle->cur) {
		int error;

		error = init_header((struct swsusp_info *)buffer);
		if (error)
			return error;
		handle->buffer = buffer;
		memory_bm_position_reset(&orig_bm);
		memory_bm_position_reset(&copy_bm);
	} else if (handle->cur <= nr_meta_pages) {
		clear_page(buffer);
		pack_pfns(buffer, &orig_bm);
	} else {
		struct page *page;

		page = pfn_to_page(memory_bm_next_pfn(&copy_bm));
		if (PageHighMem(page)) {
			/*
			 * Highmem pages are copied to the buffer,
			 * because we can't return with a kmapped
			 * highmem page (we may not be called again).
			 */
			void *kaddr;

			kaddr = kmap_atomic(page);
			copy_page(buffer, kaddr);
			kunmap_atomic(kaddr);
			handle->buffer = buffer;
		} else {
			handle->buffer = page_address(page);
		}
	}
	handle->cur++;
	return PAGE_SIZE;
}