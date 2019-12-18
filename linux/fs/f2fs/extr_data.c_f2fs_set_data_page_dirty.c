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
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  IS_ATOMIC_WRITTEN_PAGE (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int __set_page_dirty_nobuffers (struct page*) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_commit_atomic_write (struct inode*) ; 
 int /*<<< orphan*/  f2fs_register_inmem_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_update_dirty_page (struct inode*,struct page*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 int /*<<< orphan*/  trace_f2fs_set_page_dirty (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_set_data_page_dirty(struct page *page)
{
	struct inode *inode = page_file_mapping(page)->host;

	trace_f2fs_set_page_dirty(page, DATA);

	if (!PageUptodate(page))
		SetPageUptodate(page);
	if (PageSwapCache(page))
		return __set_page_dirty_nobuffers(page);

	if (f2fs_is_atomic_file(inode) && !f2fs_is_commit_atomic_write(inode)) {
		if (!IS_ATOMIC_WRITTEN_PAGE(page)) {
			f2fs_register_inmem_page(inode, page);
			return 1;
		}
		/*
		 * Previously, this page has been registered, we just
		 * return here.
		 */
		return 0;
	}

	if (!PageDirty(page)) {
		__set_page_dirty_nobuffers(page);
		f2fs_update_dirty_page(inode, page);
		return 1;
	}
	return 0;
}