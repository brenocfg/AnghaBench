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
struct btrfs_block_group_cache {int /*<<< orphan*/  reservations; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_block_group_cache*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

void btrfs_dec_block_group_reservations(struct btrfs_fs_info *fs_info,
					const u64 start)
{
	struct btrfs_block_group_cache *bg;

	bg = btrfs_lookup_block_group(fs_info, start);
	ASSERT(bg);
	if (atomic_dec_and_test(&bg->reservations))
		wake_up_var(&bg->reservations);
	btrfs_put_block_group(bg);
}