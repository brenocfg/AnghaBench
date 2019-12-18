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
struct btrfs_fs_info {int /*<<< orphan*/ * freed_extents; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_UPTODATE ; 
 int /*<<< orphan*/  set_extent_bits (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int btrfs_add_excluded_extent(struct btrfs_fs_info *fs_info,
			      u64 start, u64 num_bytes)
{
	u64 end = start + num_bytes - 1;
	set_extent_bits(&fs_info->freed_extents[0],
			start, end, EXTENT_UPTODATE);
	set_extent_bits(&fs_info->freed_extents[1],
			start, end, EXTENT_UPTODATE);
	return 0;
}