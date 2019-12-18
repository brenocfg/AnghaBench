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
struct map_lookup {int num_stripes; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {scalar_t__ const start; struct map_lookup* map_lookup; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  extent_root; struct extent_map_tree mapping_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction_fallback_global_rsv (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__ const,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct btrfs_trans_handle *btrfs_start_trans_remove_block_group(
		struct btrfs_fs_info *fs_info, const u64 chunk_offset)
{
	struct extent_map_tree *em_tree = &fs_info->mapping_tree;
	struct extent_map *em;
	struct map_lookup *map;
	unsigned int num_items;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, chunk_offset, 1);
	read_unlock(&em_tree->lock);
	ASSERT(em && em->start == chunk_offset);

	/*
	 * We need to reserve 3 + N units from the metadata space info in order
	 * to remove a block group (done at btrfs_remove_chunk() and at
	 * btrfs_remove_block_group()), which are used for:
	 *
	 * 1 unit for adding the free space inode's orphan (located in the tree
	 * of tree roots).
	 * 1 unit for deleting the block group item (located in the extent
	 * tree).
	 * 1 unit for deleting the free space item (located in tree of tree
	 * roots).
	 * N units for deleting N device extent items corresponding to each
	 * stripe (located in the device tree).
	 *
	 * In order to remove a block group we also need to reserve units in the
	 * system space info in order to update the chunk tree (update one or
	 * more device items and remove one chunk item), but this is done at
	 * btrfs_remove_chunk() through a call to check_system_chunk().
	 */
	map = em->map_lookup;
	num_items = 3 + map->num_stripes;
	free_extent_map(em);

	return btrfs_start_transaction_fallback_global_rsv(fs_info->extent_root,
							   num_items, 1);
}