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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int can_flush_pending_bgs; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {struct btrfs_root* free_space_root; struct btrfs_root* dev_root; struct btrfs_root* chunk_root; struct btrfs_root* extent_root; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 struct extent_buffer* btrfs_alloc_tree_block (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_disk_key const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct extent_buffer *alloc_tree_block_no_bg_flush(
					  struct btrfs_trans_handle *trans,
					  struct btrfs_root *root,
					  u64 parent_start,
					  const struct btrfs_disk_key *disk_key,
					  int level,
					  u64 hint,
					  u64 empty_size)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct extent_buffer *ret;

	/*
	 * If we are COWing a node/leaf from the extent, chunk, device or free
	 * space trees, make sure that we do not finish block group creation of
	 * pending block groups. We do this to avoid a deadlock.
	 * COWing can result in allocation of a new chunk, and flushing pending
	 * block groups (btrfs_create_pending_block_groups()) can be triggered
	 * when finishing allocation of a new chunk. Creation of a pending block
	 * group modifies the extent, chunk, device and free space trees,
	 * therefore we could deadlock with ourselves since we are holding a
	 * lock on an extent buffer that btrfs_create_pending_block_groups() may
	 * try to COW later.
	 * For similar reasons, we also need to delay flushing pending block
	 * groups when splitting a leaf or node, from one of those trees, since
	 * we are holding a write lock on it and its parent or when inserting a
	 * new root node for one of those trees.
	 */
	if (root == fs_info->extent_root ||
	    root == fs_info->chunk_root ||
	    root == fs_info->dev_root ||
	    root == fs_info->free_space_root)
		trans->can_flush_pending_bgs = false;

	ret = btrfs_alloc_tree_block(trans, root, parent_start,
				     root->root_key.objectid, disk_key, level,
				     hint, empty_size);
	trans->can_flush_pending_bgs = true;

	return ret;
}