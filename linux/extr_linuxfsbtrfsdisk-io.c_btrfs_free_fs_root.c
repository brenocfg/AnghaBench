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
struct btrfs_root {int /*<<< orphan*/  free_ino_pinned; int /*<<< orphan*/  free_ino_ctl; int /*<<< orphan*/  commit_root; int /*<<< orphan*/  node; scalar_t__ subv_writers; scalar_t__ anon_dev; int /*<<< orphan*/  inode_tree; int /*<<< orphan*/  ino_cache_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_free_subvolume_writers (scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_fs_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  free_anon_bdev (scalar_t__) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void btrfs_free_fs_root(struct btrfs_root *root)
{
	iput(root->ino_cache_inode);
	WARN_ON(!RB_EMPTY_ROOT(&root->inode_tree));
	if (root->anon_dev)
		free_anon_bdev(root->anon_dev);
	if (root->subv_writers)
		btrfs_free_subvolume_writers(root->subv_writers);
	free_extent_buffer(root->node);
	free_extent_buffer(root->commit_root);
	kfree(root->free_ino_ctl);
	kfree(root->free_ino_pinned);
	btrfs_put_fs_root(root);
}