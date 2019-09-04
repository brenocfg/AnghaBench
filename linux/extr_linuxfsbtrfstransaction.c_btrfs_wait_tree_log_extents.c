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
struct extent_io_tree {int dummy; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct extent_io_tree dirty_log_pages; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_FS_LOG1_ERR ; 
 int /*<<< orphan*/  BTRFS_FS_LOG2_ERR ; 
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int EIO ; 
 int EXTENT_DIRTY ; 
 int EXTENT_NEW ; 
 int __btrfs_wait_marked_extents (struct btrfs_fs_info*,struct extent_io_tree*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_wait_tree_log_extents(struct btrfs_root *log_root, int mark)
{
	struct btrfs_fs_info *fs_info = log_root->fs_info;
	struct extent_io_tree *dirty_pages = &log_root->dirty_log_pages;
	bool errors = false;
	int err;

	ASSERT(log_root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	err = __btrfs_wait_marked_extents(fs_info, dirty_pages);
	if ((mark & EXTENT_DIRTY) &&
	    test_and_clear_bit(BTRFS_FS_LOG1_ERR, &fs_info->flags))
		errors = true;

	if ((mark & EXTENT_NEW) &&
	    test_and_clear_bit(BTRFS_FS_LOG2_ERR, &fs_info->flags))
		errors = true;

	if (errors && !err)
		err = -EIO;
	return err;
}