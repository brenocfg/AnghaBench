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
struct btrfs_space_info {scalar_t__ bytes_used; scalar_t__ bytes_reserved; int /*<<< orphan*/  total_bytes; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_REMOUNTING ; 
 int /*<<< orphan*/  btrfs_calc_reclaim_metadata_size (struct btrfs_fs_info*,struct btrfs_space_info*,int) ; 
 int /*<<< orphan*/  btrfs_fs_closing (struct btrfs_fs_info*) ; 
 scalar_t__ div_factor_fine (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int need_do_async_reclaim(struct btrfs_fs_info *fs_info,
					struct btrfs_space_info *space_info,
					u64 used, bool system_chunk)
{
	u64 thresh = div_factor_fine(space_info->total_bytes, 98);

	/* If we're just plain full then async reclaim just slows us down. */
	if ((space_info->bytes_used + space_info->bytes_reserved) >= thresh)
		return 0;

	if (!btrfs_calc_reclaim_metadata_size(fs_info, space_info,
					      system_chunk))
		return 0;

	return (used >= thresh && !btrfs_fs_closing(fs_info) &&
		!test_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state));
}