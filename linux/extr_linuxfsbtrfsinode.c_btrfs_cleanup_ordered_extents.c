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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate2 (struct page*) ; 
 int const PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 void __endio_write_update_ordered (struct inode*,scalar_t__,scalar_t__,int) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static inline void btrfs_cleanup_ordered_extents(struct inode *inode,
						 const u64 offset,
						 const u64 bytes)
{
	unsigned long index = offset >> PAGE_SHIFT;
	unsigned long end_index = (offset + bytes - 1) >> PAGE_SHIFT;
	struct page *page;

	while (index <= end_index) {
		page = find_get_page(inode->i_mapping, index);
		index++;
		if (!page)
			continue;
		ClearPagePrivate2(page);
		put_page(page);
	}
	return __endio_write_update_ordered(inode, offset + PAGE_SIZE,
					    bytes - PAGE_SIZE, false);
}