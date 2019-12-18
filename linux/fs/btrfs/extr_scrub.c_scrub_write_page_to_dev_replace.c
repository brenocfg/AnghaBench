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
struct scrub_page {int /*<<< orphan*/ * page; scalar_t__ io_error; } ;
struct scrub_block {int /*<<< orphan*/  sctx; struct scrub_page** pagev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int scrub_add_page_to_wr_bio (int /*<<< orphan*/ ,struct scrub_page*) ; 

__attribute__((used)) static int scrub_write_page_to_dev_replace(struct scrub_block *sblock,
					   int page_num)
{
	struct scrub_page *spage = sblock->pagev[page_num];

	BUG_ON(spage->page == NULL);
	if (spage->io_error) {
		void *mapped_buffer = kmap_atomic(spage->page);

		clear_page(mapped_buffer);
		flush_dcache_page(spage->page);
		kunmap_atomic(mapped_buffer);
	}
	return scrub_add_page_to_wr_bio(sblock->sctx, spage);
}