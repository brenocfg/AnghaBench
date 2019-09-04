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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  pin_down_extent (struct btrfs_fs_info*,struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int btrfs_pin_extent(struct btrfs_fs_info *fs_info,
		     u64 bytenr, u64 num_bytes, int reserved)
{
	struct btrfs_block_group_cache *cache;

	cache = btrfs_lookup_block_group(fs_info, bytenr);
	BUG_ON(!cache); /* Logic error */

	pin_down_extent(fs_info, cache, bytenr, num_bytes, reserved);

	btrfs_put_block_group(cache);
	return 0;
}