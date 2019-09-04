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
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
struct TYPE_2__ {unsigned long offset; int /*<<< orphan*/  type; scalar_t__ objectid; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  free_space_lock; int /*<<< orphan*/  bg_list; int /*<<< orphan*/  cluster_list; int /*<<< orphan*/  list; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  full_stripe_len; TYPE_1__ key; void* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_ITEM_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_init_free_space_ctl (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_block_group_cache*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct btrfs_block_group_cache *
btrfs_alloc_dummy_block_group(struct btrfs_fs_info *fs_info,
			      unsigned long length)
{
	struct btrfs_block_group_cache *cache;

	cache = kzalloc(sizeof(*cache), GFP_KERNEL);
	if (!cache)
		return NULL;
	cache->free_space_ctl = kzalloc(sizeof(*cache->free_space_ctl),
					GFP_KERNEL);
	if (!cache->free_space_ctl) {
		kfree(cache);
		return NULL;
	}

	cache->key.objectid = 0;
	cache->key.offset = length;
	cache->key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;
	cache->full_stripe_len = fs_info->sectorsize;
	cache->fs_info = fs_info;

	INIT_LIST_HEAD(&cache->list);
	INIT_LIST_HEAD(&cache->cluster_list);
	INIT_LIST_HEAD(&cache->bg_list);
	btrfs_init_free_space_ctl(cache);
	mutex_init(&cache->free_space_lock);

	return cache;
}