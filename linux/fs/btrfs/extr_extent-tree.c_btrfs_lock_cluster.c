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
struct btrfs_free_cluster {struct btrfs_block_group_cache* block_group; int /*<<< orphan*/  refill_lock; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  data_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  down_read_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_block_group_cache *
btrfs_lock_cluster(struct btrfs_block_group_cache *block_group,
		   struct btrfs_free_cluster *cluster,
		   int delalloc)
{
	struct btrfs_block_group_cache *used_bg = NULL;

	spin_lock(&cluster->refill_lock);
	while (1) {
		used_bg = cluster->block_group;
		if (!used_bg)
			return NULL;

		if (used_bg == block_group)
			return used_bg;

		btrfs_get_block_group(used_bg);

		if (!delalloc)
			return used_bg;

		if (down_read_trylock(&used_bg->data_rwsem))
			return used_bg;

		spin_unlock(&cluster->refill_lock);

		/* We should only have one-level nested. */
		down_read_nested(&used_bg->data_rwsem, SINGLE_DEPTH_NESTING);

		spin_lock(&cluster->refill_lock);
		if (used_bg == cluster->block_group)
			return used_bg;

		up_read(&used_bg->data_rwsem);
		btrfs_put_block_group(used_bg);
	}
}