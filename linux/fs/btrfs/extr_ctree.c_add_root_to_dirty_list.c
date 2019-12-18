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
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {int /*<<< orphan*/  dirty_list; TYPE_1__ root_key; int /*<<< orphan*/  state; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  dirty_cowonly_roots; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_TREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_ROOT_DIRTY ; 
 int /*<<< orphan*/  BTRFS_ROOT_TRACK_DIRTY ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_root_to_dirty_list(struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (test_bit(BTRFS_ROOT_DIRTY, &root->state) ||
	    !test_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state))
		return;

	spin_lock(&fs_info->trans_lock);
	if (!test_and_set_bit(BTRFS_ROOT_DIRTY, &root->state)) {
		/* Want the extent tree to be the last on the list */
		if (root->root_key.objectid == BTRFS_EXTENT_TREE_OBJECTID)
			list_move_tail(&root->dirty_list,
				       &fs_info->dirty_cowonly_roots);
		else
			list_move(&root->dirty_list,
				  &fs_info->dirty_cowonly_roots);
	}
	spin_unlock(&fs_info->trans_lock);
}