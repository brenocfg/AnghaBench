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
struct btrfs_space_info {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {scalar_t__ sectorsize; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  ENOSPC_DEBUG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_dec_block_group_reservations (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_dump_space_info (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__,scalar_t__) ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,scalar_t__) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int find_free_extent (struct btrfs_fs_info*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct btrfs_key*,scalar_t__,int) ; 
 scalar_t__ get_alloc_profile_by_root (struct btrfs_root*,int) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ round_down (scalar_t__,scalar_t__) ; 

int btrfs_reserve_extent(struct btrfs_root *root, u64 ram_bytes,
			 u64 num_bytes, u64 min_alloc_size,
			 u64 empty_size, u64 hint_byte,
			 struct btrfs_key *ins, int is_data, int delalloc)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	bool final_tried = num_bytes == min_alloc_size;
	u64 flags;
	int ret;

	flags = get_alloc_profile_by_root(root, is_data);
again:
	WARN_ON(num_bytes < fs_info->sectorsize);
	ret = find_free_extent(fs_info, ram_bytes, num_bytes, empty_size,
			       hint_byte, ins, flags, delalloc);
	if (!ret && !is_data) {
		btrfs_dec_block_group_reservations(fs_info, ins->objectid);
	} else if (ret == -ENOSPC) {
		if (!final_tried && ins->offset) {
			num_bytes = min(num_bytes >> 1, ins->offset);
			num_bytes = round_down(num_bytes,
					       fs_info->sectorsize);
			num_bytes = max(num_bytes, min_alloc_size);
			ram_bytes = num_bytes;
			if (num_bytes == min_alloc_size)
				final_tried = true;
			goto again;
		} else if (btrfs_test_opt(fs_info, ENOSPC_DEBUG)) {
			struct btrfs_space_info *sinfo;

			sinfo = btrfs_find_space_info(fs_info, flags);
			btrfs_err(fs_info,
				  "allocation failed flags %llu, wanted %llu",
				  flags, num_bytes);
			if (sinfo)
				btrfs_dump_space_info(fs_info, sinfo,
						      num_bytes, 1);
		}
	}

	return ret;
}