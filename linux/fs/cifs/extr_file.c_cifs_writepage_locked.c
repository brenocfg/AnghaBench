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
struct writeback_control {scalar_t__ sync_mode; } ;
struct page {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_partialpagewrite (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned int get_xid () ; 
 scalar_t__ is_retryable_error (int) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 

__attribute__((used)) static int
cifs_writepage_locked(struct page *page, struct writeback_control *wbc)
{
	int rc;
	unsigned int xid;

	xid = get_xid();
/* BB add check for wbc flags */
	get_page(page);
	if (!PageUptodate(page))
		cifs_dbg(FYI, "ppw - page not up to date\n");

	/*
	 * Set the "writeback" flag, and clear "dirty" in the radix tree.
	 *
	 * A writepage() implementation always needs to do either this,
	 * or re-dirty the page with "redirty_page_for_writepage()" in
	 * the case of a failure.
	 *
	 * Just unlocking the page will cause the radix tree tag-bits
	 * to fail to update with the state of the page correctly.
	 */
	set_page_writeback(page);
retry_write:
	rc = cifs_partialpagewrite(page, 0, PAGE_SIZE);
	if (is_retryable_error(rc)) {
		if (wbc->sync_mode == WB_SYNC_ALL && rc == -EAGAIN)
			goto retry_write;
		redirty_page_for_writepage(wbc, page);
	} else if (rc != 0) {
		SetPageError(page);
		mapping_set_error(page->mapping, rc);
	} else {
		SetPageUptodate(page);
	}
	end_page_writeback(page);
	put_page(page);
	free_xid(xid);
	return rc;
}