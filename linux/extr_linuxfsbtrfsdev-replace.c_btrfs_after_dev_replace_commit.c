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
struct btrfs_dev_replace {int /*<<< orphan*/  cursor_left_last_write_of_item; int /*<<< orphan*/  committed_cursor_left; } ;
struct btrfs_fs_info {struct btrfs_dev_replace dev_replace; } ;

/* Variables and functions */

void btrfs_after_dev_replace_commit(struct btrfs_fs_info *fs_info)
{
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	dev_replace->committed_cursor_left =
		dev_replace->cursor_left_last_write_of_item;
}