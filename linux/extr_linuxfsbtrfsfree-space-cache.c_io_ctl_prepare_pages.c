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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct btrfs_io_ctl {int num_pages; struct page** pages; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {TYPE_1__* root; } ;
struct TYPE_3__ {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  btrfs_alloc_write_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btrfs_readpage (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_drop_pages (struct btrfs_io_ctl*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  set_page_extent_mapped (struct page*) ; 

__attribute__((used)) static int io_ctl_prepare_pages(struct btrfs_io_ctl *io_ctl, struct inode *inode,
				int uptodate)
{
	struct page *page;
	gfp_t mask = btrfs_alloc_write_mask(inode->i_mapping);
	int i;

	for (i = 0; i < io_ctl->num_pages; i++) {
		page = find_or_create_page(inode->i_mapping, i, mask);
		if (!page) {
			io_ctl_drop_pages(io_ctl);
			return -ENOMEM;
		}
		io_ctl->pages[i] = page;
		if (uptodate && !PageUptodate(page)) {
			btrfs_readpage(NULL, page);
			lock_page(page);
			if (!PageUptodate(page)) {
				btrfs_err(BTRFS_I(inode)->root->fs_info,
					   "error reading free space cache");
				io_ctl_drop_pages(io_ctl);
				return -EIO;
			}
		}
	}

	for (i = 0; i < io_ctl->num_pages; i++) {
		clear_page_dirty_for_io(io_ctl->pages[i]);
		set_page_extent_mapped(io_ctl->pages[i]);
	}

	return 0;
}