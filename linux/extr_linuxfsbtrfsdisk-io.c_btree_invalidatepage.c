#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_2__* mapping; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_6__ {TYPE_1__* root; struct extent_io_tree io_tree; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  btree_releasepage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  extent_invalidatepage (struct extent_io_tree*,struct page*,unsigned int) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btree_invalidatepage(struct page *page, unsigned int offset,
				 unsigned int length)
{
	struct extent_io_tree *tree;
	tree = &BTRFS_I(page->mapping->host)->io_tree;
	extent_invalidatepage(tree, page, offset);
	btree_releasepage(page, GFP_NOFS);
	if (PagePrivate(page)) {
		btrfs_warn(BTRFS_I(page->mapping->host)->root->fs_info,
			   "page private not zero on page %llu",
			   (unsigned long long)page_offset(page));
		ClearPagePrivate(page);
		set_page_private(page, 0);
		put_page(page);
	}
}