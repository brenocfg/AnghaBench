#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int PF_MEMALLOC ; 
 int /*<<< orphan*/  btrfs_add_delayed_iput (struct inode*) ; 
 TYPE_2__* current ; 
 int extent_write_full_page (struct page*,struct writeback_control*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int btrfs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	int ret;

	if (current->flags & PF_MEMALLOC) {
		redirty_page_for_writepage(wbc, page);
		unlock_page(page);
		return 0;
	}

	/*
	 * If we are under memory pressure we will call this directly from the
	 * VM, we need to make sure we have the inode referenced for the ordered
	 * extent.  If not just return like we didn't do anything.
	 */
	if (!igrab(inode)) {
		redirty_page_for_writepage(wbc, page);
		return AOP_WRITEPAGE_ACTIVATE;
	}
	ret = extent_write_full_page(page, wbc);
	btrfs_add_delayed_iput(inode);
	return ret;
}