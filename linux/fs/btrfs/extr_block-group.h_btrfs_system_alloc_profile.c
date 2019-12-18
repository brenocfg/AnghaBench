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

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 int /*<<< orphan*/  btrfs_get_alloc_profile (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 btrfs_system_alloc_profile(struct btrfs_fs_info *fs_info)
{
	return btrfs_get_alloc_profile(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
}