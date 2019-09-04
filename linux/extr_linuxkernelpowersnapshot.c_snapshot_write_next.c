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
struct snapshot_handle {int cur; int sync_read; void* buffer; } ;
struct chain_allocator {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PG_ANY ; 
 int /*<<< orphan*/  PG_SAFE ; 
 int PTR_ERR (void*) ; 
 void* buffer ; 
 int /*<<< orphan*/  chain_init (struct chain_allocator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_bm ; 
 int /*<<< orphan*/  copy_last_highmem_page () ; 
 void* get_buffer (int /*<<< orphan*/ *,struct chain_allocator*) ; 
 void* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hibernate_restore_protect_page (void*) ; 
 int /*<<< orphan*/  hibernate_restore_protection_begin () ; 
 int load_header (void*) ; 
 int memory_bm_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ *) ; 
 int nr_copy_pages ; 
 int nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 
 int page_key_alloc (int) ; 
 int /*<<< orphan*/  page_key_write (void*) ; 
 int prepare_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * restore_pblist ; 
 int /*<<< orphan*/ * safe_pages_list ; 
 int unpack_orig_pfns (void*,int /*<<< orphan*/ *) ; 

int snapshot_write_next(struct snapshot_handle *handle)
{
	static struct chain_allocator ca;
	int error = 0;

	/* Check if we have already loaded the entire image */
	if (handle->cur > 1 && handle->cur > nr_meta_pages + nr_copy_pages)
		return 0;

	handle->sync_read = 1;

	if (!handle->cur) {
		if (!buffer)
			/* This makes the buffer be freed by swsusp_free() */
			buffer = get_image_page(GFP_ATOMIC, PG_ANY);

		if (!buffer)
			return -ENOMEM;

		handle->buffer = buffer;
	} else if (handle->cur == 1) {
		error = load_header(buffer);
		if (error)
			return error;

		safe_pages_list = NULL;

		error = memory_bm_create(&copy_bm, GFP_ATOMIC, PG_ANY);
		if (error)
			return error;

		/* Allocate buffer for page keys. */
		error = page_key_alloc(nr_copy_pages);
		if (error)
			return error;

		hibernate_restore_protection_begin();
	} else if (handle->cur <= nr_meta_pages + 1) {
		error = unpack_orig_pfns(buffer, &copy_bm);
		if (error)
			return error;

		if (handle->cur == nr_meta_pages + 1) {
			error = prepare_image(&orig_bm, &copy_bm);
			if (error)
				return error;

			chain_init(&ca, GFP_ATOMIC, PG_SAFE);
			memory_bm_position_reset(&orig_bm);
			restore_pblist = NULL;
			handle->buffer = get_buffer(&orig_bm, &ca);
			handle->sync_read = 0;
			if (IS_ERR(handle->buffer))
				return PTR_ERR(handle->buffer);
		}
	} else {
		copy_last_highmem_page();
		/* Restore page key for data page (s390 only). */
		page_key_write(handle->buffer);
		hibernate_restore_protect_page(handle->buffer);
		handle->buffer = get_buffer(&orig_bm, &ca);
		if (IS_ERR(handle->buffer))
			return PTR_ERR(handle->buffer);
		if (handle->buffer != buffer)
			handle->sync_read = 0;
	}
	handle->cur++;
	return PAGE_SIZE;
}