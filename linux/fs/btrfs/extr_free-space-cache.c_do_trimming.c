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
struct btrfs_trim_range {int /*<<< orphan*/  list; } ;
struct btrfs_space_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_reserved; int /*<<< orphan*/  bytes_readonly; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_ctl {int /*<<< orphan*/  cache_writeout_mutex; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  reserved; scalar_t__ ro; struct btrfs_free_space_ctl* free_space_ctl; struct btrfs_fs_info* fs_info; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_add_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int btrfs_discard_extent (struct btrfs_fs_info*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_trimming(struct btrfs_block_group_cache *block_group,
		       u64 *total_trimmed, u64 start, u64 bytes,
		       u64 reserved_start, u64 reserved_bytes,
		       struct btrfs_trim_range *trim_entry)
{
	struct btrfs_space_info *space_info = block_group->space_info;
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	int ret;
	int update = 0;
	u64 trimmed = 0;

	spin_lock(&space_info->lock);
	spin_lock(&block_group->lock);
	if (!block_group->ro) {
		block_group->reserved += reserved_bytes;
		space_info->bytes_reserved += reserved_bytes;
		update = 1;
	}
	spin_unlock(&block_group->lock);
	spin_unlock(&space_info->lock);

	ret = btrfs_discard_extent(fs_info, start, bytes, &trimmed);
	if (!ret)
		*total_trimmed += trimmed;

	mutex_lock(&ctl->cache_writeout_mutex);
	btrfs_add_free_space(block_group, reserved_start, reserved_bytes);
	list_del(&trim_entry->list);
	mutex_unlock(&ctl->cache_writeout_mutex);

	if (update) {
		spin_lock(&space_info->lock);
		spin_lock(&block_group->lock);
		if (block_group->ro)
			space_info->bytes_readonly += reserved_bytes;
		block_group->reserved -= reserved_bytes;
		space_info->bytes_reserved -= reserved_bytes;
		spin_unlock(&block_group->lock);
		spin_unlock(&space_info->lock);
	}

	return ret;
}