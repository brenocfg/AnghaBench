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
struct btrfs_block_group_cache {int /*<<< orphan*/  data_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
btrfs_grab_block_group(struct btrfs_block_group_cache *cache,
		       int delalloc)
{
	btrfs_get_block_group(cache);
	if (delalloc)
		down_read(&cache->data_rwsem);
}