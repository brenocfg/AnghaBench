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
typedef  scalar_t__ u32 ;
struct btrfs_header {int dummy; } ;
struct btrfs_fs_info {scalar_t__ nodesize; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 BTRFS_LEAF_DATA_SIZE(const struct btrfs_fs_info *info)
{

	return info->nodesize - sizeof(struct btrfs_header);
}