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
 int /*<<< orphan*/  F2FS_DIRTY_META ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 int /*<<< orphan*/  META ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  f2fs_set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_trace_pid (struct page*) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_set_page_dirty (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_set_meta_page_dirty(struct page *page)
{
	trace_f2fs_set_page_dirty(page, META);

	if (!PageUptodate(page))
		SetPageUptodate(page);
	if (!PageDirty(page)) {
		__set_page_dirty_nobuffers(page);
		inc_page_count(F2FS_P_SB(page), F2FS_DIRTY_META);
		f2fs_set_page_private(page, 0);
		f2fs_trace_pid(page);
		return 1;
	}
	return 0;
}