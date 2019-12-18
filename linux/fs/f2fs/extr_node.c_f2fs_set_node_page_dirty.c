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
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 scalar_t__ IS_INODE (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  f2fs_inode_chksum_set (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  f2fs_set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_trace_pid (struct page*) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_set_page_dirty (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_set_node_page_dirty(struct page *page)
{
	trace_f2fs_set_page_dirty(page, NODE);

	if (!PageUptodate(page))
		SetPageUptodate(page);
#ifdef CONFIG_F2FS_CHECK_FS
	if (IS_INODE(page))
		f2fs_inode_chksum_set(F2FS_P_SB(page), page);
#endif
	if (!PageDirty(page)) {
		__set_page_dirty_nobuffers(page);
		inc_page_count(F2FS_P_SB(page), F2FS_DIRTY_NODES);
		f2fs_set_page_private(page, 0);
		f2fs_trace_pid(page);
		return 1;
	}
	return 0;
}