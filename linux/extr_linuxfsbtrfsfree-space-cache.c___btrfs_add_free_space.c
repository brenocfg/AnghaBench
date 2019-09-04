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
typedef  void* u64 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_ctl {int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {int /*<<< orphan*/  offset_index; void* bytes; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_crit (struct btrfs_fs_info*,char*,int) ; 
 int /*<<< orphan*/  btrfs_free_space_cachep ; 
 int insert_into_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_free_space*) ; 
 struct btrfs_free_space* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int link_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steal_from_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int) ; 
 scalar_t__ try_merge_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int) ; 

int __btrfs_add_free_space(struct btrfs_fs_info *fs_info,
			   struct btrfs_free_space_ctl *ctl,
			   u64 offset, u64 bytes)
{
	struct btrfs_free_space *info;
	int ret = 0;

	info = kmem_cache_zalloc(btrfs_free_space_cachep, GFP_NOFS);
	if (!info)
		return -ENOMEM;

	info->offset = offset;
	info->bytes = bytes;
	RB_CLEAR_NODE(&info->offset_index);

	spin_lock(&ctl->tree_lock);

	if (try_merge_free_space(ctl, info, true))
		goto link;

	/*
	 * There was no extent directly to the left or right of this new
	 * extent then we know we're going to have to allocate a new extent, so
	 * before we do that see if we need to drop this into a bitmap
	 */
	ret = insert_into_bitmap(ctl, info);
	if (ret < 0) {
		goto out;
	} else if (ret) {
		ret = 0;
		goto out;
	}
link:
	/*
	 * Only steal free space from adjacent bitmaps if we're sure we're not
	 * going to add the new free space to existing bitmap entries - because
	 * that would mean unnecessary work that would be reverted. Therefore
	 * attempt to steal space from bitmaps if we're adding an extent entry.
	 */
	steal_from_bitmap(ctl, info, true);

	ret = link_free_space(ctl, info);
	if (ret)
		kmem_cache_free(btrfs_free_space_cachep, info);
out:
	spin_unlock(&ctl->tree_lock);

	if (ret) {
		btrfs_crit(fs_info, "unable to add free space :%d", ret);
		ASSERT(ret != -EEXIST);
	}

	return ret;
}