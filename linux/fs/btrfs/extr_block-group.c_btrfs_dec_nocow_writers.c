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
struct btrfs_block_group_cache {int /*<<< orphan*/  nocow_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_block_group_cache*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

void btrfs_dec_nocow_writers(struct btrfs_fs_info *fs_info, u64 bytenr)
{
	struct btrfs_block_group_cache *bg;

	bg = btrfs_lookup_block_group(fs_info, bytenr);
	ASSERT(bg);
	if (atomic_dec_and_test(&bg->nocow_writers))
		wake_up_var(&bg->nocow_writers);
	/*
	 * Once for our lookup and once for the lookup done by a previous call
	 * to btrfs_inc_nocow_writers()
	 */
	btrfs_put_block_group(bg);
	btrfs_put_block_group(bg);
}