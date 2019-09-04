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
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int fuse_writepage_locked (struct page*) ; 

__attribute__((used)) static int fuse_launder_page(struct page *page)
{
	int err = 0;
	if (clear_page_dirty_for_io(page)) {
		struct inode *inode = page->mapping->host;
		err = fuse_writepage_locked(page);
		if (!err)
			fuse_wait_on_page_writeback(inode, page->index);
	}
	return err;
}