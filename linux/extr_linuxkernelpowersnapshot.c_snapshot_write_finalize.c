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
struct snapshot_handle {int cur; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_last_highmem_page () ; 
 int /*<<< orphan*/  free_highmem_data () ; 
 int /*<<< orphan*/  hibernate_restore_protect_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_recycle (int /*<<< orphan*/ *) ; 
 int nr_copy_pages ; 
 int nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 
 int /*<<< orphan*/  page_key_free () ; 
 int /*<<< orphan*/  page_key_write (int /*<<< orphan*/ ) ; 

void snapshot_write_finalize(struct snapshot_handle *handle)
{
	copy_last_highmem_page();
	/* Restore page key for data page (s390 only). */
	page_key_write(handle->buffer);
	page_key_free();
	hibernate_restore_protect_page(handle->buffer);
	/* Do that only if we have loaded the image entirely */
	if (handle->cur > 1 && handle->cur > nr_meta_pages + nr_copy_pages) {
		memory_bm_recycle(&orig_bm);
		free_highmem_data();
	}
}