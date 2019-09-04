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
struct btrfs_space_info {int flags; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 

__attribute__((used)) static inline bool btrfs_mixed_space_info(struct btrfs_space_info *space_info)
{
	return ((space_info->flags & BTRFS_BLOCK_GROUP_METADATA) &&
		(space_info->flags & BTRFS_BLOCK_GROUP_DATA));
}