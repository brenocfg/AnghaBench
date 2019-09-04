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
typedef  unsigned long u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct extent_io_tree {struct inode* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct page*) ; 
 unsigned long PAGE_SHIFT ; 
 struct page* find_get_page (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 

void btrfs_set_range_writeback(struct extent_io_tree *tree, u64 start, u64 end)
{
	struct inode *inode = tree->private_data;
	unsigned long index = start >> PAGE_SHIFT;
	unsigned long end_index = end >> PAGE_SHIFT;
	struct page *page;

	while (index <= end_index) {
		page = find_get_page(inode->i_mapping, index);
		ASSERT(page); /* Pages should be in the extent_io_tree */
		set_page_writeback(page);
		put_page(page);
		index++;
	}
}