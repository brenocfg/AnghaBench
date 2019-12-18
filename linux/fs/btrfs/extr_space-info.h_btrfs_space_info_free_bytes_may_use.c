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
struct btrfs_space_info {int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_space_info_update_bytes_may_use (struct btrfs_fs_info*,struct btrfs_space_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_try_granting_tickets (struct btrfs_fs_info*,struct btrfs_space_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_space_info_free_bytes_may_use(
				struct btrfs_fs_info *fs_info,
				struct btrfs_space_info *space_info,
				u64 num_bytes)
{
	spin_lock(&space_info->lock);
	btrfs_space_info_update_bytes_may_use(fs_info, space_info, -num_bytes);
	btrfs_try_granting_tickets(fs_info, space_info);
	spin_unlock(&space_info->lock);
}