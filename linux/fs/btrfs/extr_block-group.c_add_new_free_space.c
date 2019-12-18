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
struct btrfs_fs_info {int /*<<< orphan*/  pinned_extents; } ;
struct btrfs_block_group_cache {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXTENT_DIRTY ; 
 int EXTENT_UPTODATE ; 
 int btrfs_add_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int find_first_extent_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ *) ; 

u64 add_new_free_space(struct btrfs_block_group_cache *block_group,
		       u64 start, u64 end)
{
	struct btrfs_fs_info *info = block_group->fs_info;
	u64 extent_start, extent_end, size, total_added = 0;
	int ret;

	while (start < end) {
		ret = find_first_extent_bit(info->pinned_extents, start,
					    &extent_start, &extent_end,
					    EXTENT_DIRTY | EXTENT_UPTODATE,
					    NULL);
		if (ret)
			break;

		if (extent_start <= start) {
			start = extent_end + 1;
		} else if (extent_start > start && extent_start < end) {
			size = extent_start - start;
			total_added += size;
			ret = btrfs_add_free_space(block_group, start,
						   size);
			BUG_ON(ret); /* -ENOMEM or logic error */
			start = extent_end + 1;
		} else {
			break;
		}
	}

	if (start < end) {
		size = end - start;
		total_added += size;
		ret = btrfs_add_free_space(block_group, start, size);
		BUG_ON(ret); /* -ENOMEM or logic error */
	}

	return total_added;
}