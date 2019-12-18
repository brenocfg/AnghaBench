#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ objectid; } ;
struct btrfs_root {scalar_t__ free_ino_ctl; scalar_t__ free_ino_pinned; TYPE_2__* reloc_root; int /*<<< orphan*/  root_item; TYPE_1__ root_key; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_state; int /*<<< orphan*/  subvol_srcu; int /*<<< orphan*/  fs_roots_radix_lock; int /*<<< orphan*/  fs_roots_radix; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_root; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_ERROR ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (scalar_t__) ; 
 int /*<<< orphan*/  btrfs_free_fs_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_log (int /*<<< orphan*/ *,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_put_fs_root (TYPE_2__*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_drop_and_free_fs_root(struct btrfs_fs_info *fs_info,
				  struct btrfs_root *root)
{
	spin_lock(&fs_info->fs_roots_radix_lock);
	radix_tree_delete(&fs_info->fs_roots_radix,
			  (unsigned long)root->root_key.objectid);
	spin_unlock(&fs_info->fs_roots_radix_lock);

	if (btrfs_root_refs(&root->root_item) == 0)
		synchronize_srcu(&fs_info->subvol_srcu);

	if (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) {
		btrfs_free_log(NULL, root);
		if (root->reloc_root) {
			free_extent_buffer(root->reloc_root->node);
			free_extent_buffer(root->reloc_root->commit_root);
			btrfs_put_fs_root(root->reloc_root);
			root->reloc_root = NULL;
		}
	}

	if (root->free_ino_pinned)
		__btrfs_remove_free_space_cache(root->free_ino_pinned);
	if (root->free_ino_ctl)
		__btrfs_remove_free_space_cache(root->free_ino_ctl);
	btrfs_free_fs_root(root);
}