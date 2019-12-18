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

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  dec_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_clear_page_cache_dirty_tag (struct page*) ; 

__attribute__((used)) static void clear_node_page_dirty(struct page *page)
{
	if (PageDirty(page)) {
		f2fs_clear_page_cache_dirty_tag(page);
		clear_page_dirty_for_io(page);
		dec_page_count(F2FS_P_SB(page), F2FS_DIRTY_NODES);
	}
	ClearPageUptodate(page);
}