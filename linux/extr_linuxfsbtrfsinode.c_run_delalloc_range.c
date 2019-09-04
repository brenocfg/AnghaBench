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
typedef  scalar_t__ u64 ;
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_HAS_ASYNC_EXTENT ; 
 int BTRFS_INODE_NODATACOW ; 
 int BTRFS_INODE_PREALLOC ; 
 int /*<<< orphan*/  btrfs_cleanup_ordered_extents (struct inode*,scalar_t__,scalar_t__) ; 
 int cow_file_range (struct inode*,struct page*,scalar_t__,scalar_t__,scalar_t__,int*,unsigned long*,int,int /*<<< orphan*/ *) ; 
 int cow_file_range_async (struct inode*,struct page*,scalar_t__,scalar_t__,int*,unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  inode_need_compress (struct inode*,scalar_t__,scalar_t__) ; 
 int need_force_cow (struct inode*,scalar_t__,scalar_t__) ; 
 int run_delalloc_nocow (struct inode*,struct page*,scalar_t__,scalar_t__,int*,int,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int wbc_to_write_flags (struct writeback_control*) ; 

__attribute__((used)) static int run_delalloc_range(void *private_data, struct page *locked_page,
			      u64 start, u64 end, int *page_started,
			      unsigned long *nr_written,
			      struct writeback_control *wbc)
{
	struct inode *inode = private_data;
	int ret;
	int force_cow = need_force_cow(inode, start, end);
	unsigned int write_flags = wbc_to_write_flags(wbc);

	if (BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW && !force_cow) {
		ret = run_delalloc_nocow(inode, locked_page, start, end,
					 page_started, 1, nr_written);
	} else if (BTRFS_I(inode)->flags & BTRFS_INODE_PREALLOC && !force_cow) {
		ret = run_delalloc_nocow(inode, locked_page, start, end,
					 page_started, 0, nr_written);
	} else if (!inode_need_compress(inode, start, end)) {
		ret = cow_file_range(inode, locked_page, start, end, end,
				      page_started, nr_written, 1, NULL);
	} else {
		set_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
			&BTRFS_I(inode)->runtime_flags);
		ret = cow_file_range_async(inode, locked_page, start, end,
					   page_started, nr_written,
					   write_flags);
	}
	if (ret)
		btrfs_cleanup_ordered_extents(inode, start, end - start + 1);
	return ret;
}