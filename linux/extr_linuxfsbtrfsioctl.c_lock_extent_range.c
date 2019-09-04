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
struct inode {int dummy; } ;
struct btrfs_ordered_extent {scalar_t__ file_offset; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  EXTENT_DELALLOC ; 
 struct btrfs_ordered_extent* btrfs_lookup_first_ordered_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_range (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lock_extent (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_range_bit (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lock_extent_range(struct inode *inode, u64 off, u64 len,
			     bool retry_range_locking)
{
	/*
	 * Do any pending delalloc/csum calculations on inode, one way or
	 * another, and lock file content.
	 * The locking order is:
	 *
	 *   1) pages
	 *   2) range in the inode's io tree
	 */
	while (1) {
		struct btrfs_ordered_extent *ordered;
		lock_extent(&BTRFS_I(inode)->io_tree, off, off + len - 1);
		ordered = btrfs_lookup_first_ordered_extent(inode,
							    off + len - 1);
		if ((!ordered ||
		     ordered->file_offset + ordered->len <= off ||
		     ordered->file_offset >= off + len) &&
		    !test_range_bit(&BTRFS_I(inode)->io_tree, off,
				    off + len - 1, EXTENT_DELALLOC, 0, NULL)) {
			if (ordered)
				btrfs_put_ordered_extent(ordered);
			break;
		}
		unlock_extent(&BTRFS_I(inode)->io_tree, off, off + len - 1);
		if (ordered)
			btrfs_put_ordered_extent(ordered);
		if (!retry_range_locking)
			return -EAGAIN;
		btrfs_wait_ordered_range(inode, off, len);
	}
	return 0;
}