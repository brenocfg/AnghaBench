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
struct writeback_control {int dummy; } ;
struct page {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int v9fs_vfs_writepage_locked (struct page*) ; 

__attribute__((used)) static int v9fs_vfs_writepage(struct page *page, struct writeback_control *wbc)
{
	int retval;

	p9_debug(P9_DEBUG_VFS, "page %p\n", page);

	retval = v9fs_vfs_writepage_locked(page);
	if (retval < 0) {
		if (retval == -EAGAIN) {
			redirty_page_for_writepage(wbc, page);
			retval = 0;
		} else {
			SetPageError(page);
			mapping_set_error(page->mapping, retval);
		}
	} else
		retval = 0;

	unlock_page(page);
	return retval;
}