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
typedef  scalar_t__ u64 ;
struct map_lookup {int num_stripes; TYPE_1__* stripes; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {scalar_t__ len; scalar_t__ start; struct map_lookup* map_lookup; } ;
struct btrfs_fs_info {struct extent_map_tree mapping_tree; } ;
struct btrfs_device {int dummy; } ;
struct TYPE_2__ {struct btrfs_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_dev_replace_update_device_in_mapping_tree(
						struct btrfs_fs_info *fs_info,
						struct btrfs_device *srcdev,
						struct btrfs_device *tgtdev)
{
	struct extent_map_tree *em_tree = &fs_info->mapping_tree;
	struct extent_map *em;
	struct map_lookup *map;
	u64 start = 0;
	int i;

	write_lock(&em_tree->lock);
	do {
		em = lookup_extent_mapping(em_tree, start, (u64)-1);
		if (!em)
			break;
		map = em->map_lookup;
		for (i = 0; i < map->num_stripes; i++)
			if (srcdev == map->stripes[i].dev)
				map->stripes[i].dev = tgtdev;
		start = em->start + em->len;
		free_extent_map(em);
	} while (start);
	write_unlock(&em_tree->lock);
}