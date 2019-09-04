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
struct dax_ctx {struct page*** pages; } ;

/* Variables and functions */
 int NUM_STREAM_TYPES ; 
 int OUT ; 
 int /*<<< orphan*/  dax_dbg (char*,struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static void dax_unlock_pages(struct dax_ctx *ctx, int ccb_index, int nelem)
{
	int i, j;

	for (i = ccb_index; i < ccb_index + nelem; i++) {
		for (j = 0; j < NUM_STREAM_TYPES; j++) {
			struct page *p = ctx->pages[i][j];

			if (p) {
				dax_dbg("freeing page %p", p);
				if (j == OUT)
					set_page_dirty(p);
				put_page(p);
				ctx->pages[i][j] = NULL;
			}
		}
	}
}