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
struct btrfs_ordered_extent {int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; scalar_t__ len; scalar_t__ file_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ORDERED_COMPLETE ; 
 int /*<<< orphan*/  BTRFS_ORDERED_DIRECT ; 
 int /*<<< orphan*/  filemap_fdatawrite_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_ordered_extent_start (struct inode*,struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btrfs_start_ordered_extent(struct inode *inode,
				       struct btrfs_ordered_extent *entry,
				       int wait)
{
	u64 start = entry->file_offset;
	u64 end = start + entry->len - 1;

	trace_btrfs_ordered_extent_start(inode, entry);

	/*
	 * pages in the range can be dirty, clean or writeback.  We
	 * start IO on any dirty ones so the wait doesn't stall waiting
	 * for the flusher thread to find them
	 */
	if (!test_bit(BTRFS_ORDERED_DIRECT, &entry->flags))
		filemap_fdatawrite_range(inode->i_mapping, start, end);
	if (wait) {
		wait_event(entry->wait, test_bit(BTRFS_ORDERED_COMPLETE,
						 &entry->flags));
	}
}