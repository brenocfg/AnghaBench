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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct btrfs_ordered_extent {scalar_t__ file_offset; scalar_t__ len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ORDERED_IOERR ; 
 int EIO ; 
 scalar_t__ INT_LIMIT (int /*<<< orphan*/ ) ; 
 int btrfs_fdatawrite_range (struct inode*,scalar_t__,scalar_t__) ; 
 struct btrfs_ordered_extent* btrfs_lookup_first_ordered_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (struct inode*,struct btrfs_ordered_extent*,int) ; 
 int filemap_fdatawait_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  loff_t ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_wait_ordered_range(struct inode *inode, u64 start, u64 len)
{
	int ret = 0;
	int ret_wb = 0;
	u64 end;
	u64 orig_end;
	struct btrfs_ordered_extent *ordered;

	if (start + len < start) {
		orig_end = INT_LIMIT(loff_t);
	} else {
		orig_end = start + len - 1;
		if (orig_end > INT_LIMIT(loff_t))
			orig_end = INT_LIMIT(loff_t);
	}

	/* start IO across the range first to instantiate any delalloc
	 * extents
	 */
	ret = btrfs_fdatawrite_range(inode, start, orig_end);
	if (ret)
		return ret;

	/*
	 * If we have a writeback error don't return immediately. Wait first
	 * for any ordered extents that haven't completed yet. This is to make
	 * sure no one can dirty the same page ranges and call writepages()
	 * before the ordered extents complete - to avoid failures (-EEXIST)
	 * when adding the new ordered extents to the ordered tree.
	 */
	ret_wb = filemap_fdatawait_range(inode->i_mapping, start, orig_end);

	end = orig_end;
	while (1) {
		ordered = btrfs_lookup_first_ordered_extent(inode, end);
		if (!ordered)
			break;
		if (ordered->file_offset > orig_end) {
			btrfs_put_ordered_extent(ordered);
			break;
		}
		if (ordered->file_offset + ordered->len <= start) {
			btrfs_put_ordered_extent(ordered);
			break;
		}
		btrfs_start_ordered_extent(inode, ordered, 1);
		end = ordered->file_offset;
		if (test_bit(BTRFS_ORDERED_IOERR, &ordered->flags))
			ret = -EIO;
		btrfs_put_ordered_extent(ordered);
		if (ret || end == 0 || end == start)
			break;
		end--;
	}
	return ret_wb ? ret_wb : ret;
}