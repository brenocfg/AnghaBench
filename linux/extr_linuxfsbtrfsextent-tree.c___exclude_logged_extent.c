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
struct btrfs_fs_info {int dummy; } ;
struct btrfs_caching_control {scalar_t__ progress; int /*<<< orphan*/  mutex; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int add_excluded_extent (struct btrfs_fs_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  block_group_cache_done (struct btrfs_block_group_cache*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int btrfs_remove_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cache_block_group (struct btrfs_block_group_cache*,int /*<<< orphan*/ ) ; 
 struct btrfs_caching_control* get_caching_control (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_caching_control (struct btrfs_caching_control*) ; 

__attribute__((used)) static int __exclude_logged_extent(struct btrfs_fs_info *fs_info,
				   u64 start, u64 num_bytes)
{
	int ret;
	struct btrfs_block_group_cache *block_group;
	struct btrfs_caching_control *caching_ctl;

	block_group = btrfs_lookup_block_group(fs_info, start);
	if (!block_group)
		return -EINVAL;

	cache_block_group(block_group, 0);
	caching_ctl = get_caching_control(block_group);

	if (!caching_ctl) {
		/* Logic error */
		BUG_ON(!block_group_cache_done(block_group));
		ret = btrfs_remove_free_space(block_group, start, num_bytes);
	} else {
		mutex_lock(&caching_ctl->mutex);

		if (start >= caching_ctl->progress) {
			ret = add_excluded_extent(fs_info, start, num_bytes);
		} else if (start + num_bytes <= caching_ctl->progress) {
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
		} else {
			num_bytes = caching_ctl->progress - start;
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
			if (ret)
				goto out_lock;

			num_bytes = (start + num_bytes) -
				caching_ctl->progress;
			start = caching_ctl->progress;
			ret = add_excluded_extent(fs_info, start, num_bytes);
		}
out_lock:
		mutex_unlock(&caching_ctl->mutex);
		put_caching_control(caching_ctl);
	}
	btrfs_put_block_group(block_group);
	return ret;
}