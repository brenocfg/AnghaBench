#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct scrub_block {int page_count; scalar_t__ sparity; TYPE_2__** pagev; int /*<<< orphan*/  data_corrected; TYPE_1__* sctx; int /*<<< orphan*/  no_io_error_seen; } ;
struct TYPE_4__ {scalar_t__ logical; } ;
struct TYPE_3__ {scalar_t__ is_dev_replace; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int scrub_checksum (struct scrub_block*) ; 
 int /*<<< orphan*/  scrub_handle_errored_block (struct scrub_block*) ; 
 int /*<<< orphan*/  scrub_parity_mark_sectors_error (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scrub_write_block_to_dev_replace (struct scrub_block*) ; 

__attribute__((used)) static void scrub_block_complete(struct scrub_block *sblock)
{
	int corrupted = 0;

	if (!sblock->no_io_error_seen) {
		corrupted = 1;
		scrub_handle_errored_block(sblock);
	} else {
		/*
		 * if has checksum error, write via repair mechanism in
		 * dev replace case, otherwise write here in dev replace
		 * case.
		 */
		corrupted = scrub_checksum(sblock);
		if (!corrupted && sblock->sctx->is_dev_replace)
			scrub_write_block_to_dev_replace(sblock);
	}

	if (sblock->sparity && corrupted && !sblock->data_corrected) {
		u64 start = sblock->pagev[0]->logical;
		u64 end = sblock->pagev[sblock->page_count - 1]->logical +
			  PAGE_SIZE;

		scrub_parity_mark_sectors_error(sblock->sparity,
						start, end - start);
	}
}