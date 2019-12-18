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
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  chunk_mutex; struct extent_map_tree mapping_tree; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_ctl; TYPE_1__ key; int /*<<< orphan*/  lock; scalar_t__ removed; int /*<<< orphan*/  trimming; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_extent_mapping (struct extent_map_tree*,struct extent_map*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_put_block_group_trimming(struct btrfs_block_group_cache *block_group)
{
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct extent_map_tree *em_tree;
	struct extent_map *em;
	bool cleanup;

	spin_lock(&block_group->lock);
	cleanup = (atomic_dec_and_test(&block_group->trimming) &&
		   block_group->removed);
	spin_unlock(&block_group->lock);

	if (cleanup) {
		mutex_lock(&fs_info->chunk_mutex);
		em_tree = &fs_info->mapping_tree;
		write_lock(&em_tree->lock);
		em = lookup_extent_mapping(em_tree, block_group->key.objectid,
					   1);
		BUG_ON(!em); /* logic error, can't happen */
		remove_extent_mapping(em_tree, em);
		write_unlock(&em_tree->lock);
		mutex_unlock(&fs_info->chunk_mutex);

		/* once for us and once for the tree */
		free_extent_map(em);
		free_extent_map(em);

		/*
		 * We've left one free space entry and other tasks trimming
		 * this block group have left 1 entry each one. Free them.
		 */
		__btrfs_remove_free_space_cache(block_group->free_space_ctl);
	}
}