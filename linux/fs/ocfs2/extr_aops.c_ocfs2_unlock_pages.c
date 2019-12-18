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
struct ocfs2_write_ctxt {int w_num_pages; int /*<<< orphan*/ ** w_pages; int /*<<< orphan*/ * w_target_page; scalar_t__ w_target_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mark_page_accessed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_unlock_and_free_pages (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_unlock_pages(struct ocfs2_write_ctxt *wc)
{
	int i;

	/*
	 * w_target_locked is only set to true in the page_mkwrite() case.
	 * The intent is to allow us to lock the target page from write_begin()
	 * to write_end(). The caller must hold a ref on w_target_page.
	 */
	if (wc->w_target_locked) {
		BUG_ON(!wc->w_target_page);
		for (i = 0; i < wc->w_num_pages; i++) {
			if (wc->w_target_page == wc->w_pages[i]) {
				wc->w_pages[i] = NULL;
				break;
			}
		}
		mark_page_accessed(wc->w_target_page);
		put_page(wc->w_target_page);
	}
	ocfs2_unlock_and_free_pages(wc->w_pages, wc->w_num_pages);
}