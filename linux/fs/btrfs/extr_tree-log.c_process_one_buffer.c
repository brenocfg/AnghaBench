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
typedef  int /*<<< orphan*/  u64 ;
struct walk_control {scalar_t__ wait; scalar_t__ write; scalar_t__ pin; } ;
struct extent_buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXED_GROUPS ; 
 scalar_t__ btrfs_buffer_uptodate (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_exclude_logged_extents (struct extent_buffer*) ; 
 scalar_t__ btrfs_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_pin_extent_for_log_replay (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_read_buffer (struct extent_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_wait_tree_block_writeback (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_write_tree_block (struct extent_buffer*) ; 

__attribute__((used)) static int process_one_buffer(struct btrfs_root *log,
			      struct extent_buffer *eb,
			      struct walk_control *wc, u64 gen, int level)
{
	struct btrfs_fs_info *fs_info = log->fs_info;
	int ret = 0;

	/*
	 * If this fs is mixed then we need to be able to process the leaves to
	 * pin down any logged extents, so we have to read the block.
	 */
	if (btrfs_fs_incompat(fs_info, MIXED_GROUPS)) {
		ret = btrfs_read_buffer(eb, gen, level, NULL);
		if (ret)
			return ret;
	}

	if (wc->pin)
		ret = btrfs_pin_extent_for_log_replay(fs_info, eb->start,
						      eb->len);

	if (!ret && btrfs_buffer_uptodate(eb, gen, 0)) {
		if (wc->pin && btrfs_header_level(eb) == 0)
			ret = btrfs_exclude_logged_extents(eb);
		if (wc->write)
			btrfs_write_tree_block(eb);
		if (wc->wait)
			btrfs_wait_tree_block_writeback(eb);
	}
	return ret;
}