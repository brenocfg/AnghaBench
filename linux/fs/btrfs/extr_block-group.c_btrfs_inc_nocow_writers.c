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
struct btrfs_block_group_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  nocow_writers; scalar_t__ ro; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool btrfs_inc_nocow_writers(struct btrfs_fs_info *fs_info, u64 bytenr)
{
	struct btrfs_block_group_cache *bg;
	bool ret = true;

	bg = btrfs_lookup_block_group(fs_info, bytenr);
	if (!bg)
		return false;

	spin_lock(&bg->lock);
	if (bg->ro)
		ret = false;
	else
		atomic_inc(&bg->nocow_writers);
	spin_unlock(&bg->lock);

	/* No put on block group, done by btrfs_dec_nocow_writers */
	if (!ret)
		btrfs_put_block_group(bg);

	return ret;
}