#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct kioctx {int nr_pages; struct page** ring_pages; struct page** internal_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_aio_ring_file (struct kioctx*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void aio_free_ring(struct kioctx *ctx)
{
	int i;

	/* Disconnect the kiotx from the ring file.  This prevents future
	 * accesses to the kioctx from page migration.
	 */
	put_aio_ring_file(ctx);

	for (i = 0; i < ctx->nr_pages; i++) {
		struct page *page;
		pr_debug("pid(%d) [%d] page->count=%d\n", current->pid, i,
				page_count(ctx->ring_pages[i]));
		page = ctx->ring_pages[i];
		if (!page)
			continue;
		ctx->ring_pages[i] = NULL;
		put_page(page);
	}

	if (ctx->ring_pages && ctx->ring_pages != ctx->internal_pages) {
		kfree(ctx->ring_pages);
		ctx->ring_pages = NULL;
	}
}