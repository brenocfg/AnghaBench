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
struct btrfs_ordered_sum {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  super_copy; int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int btrfs_super_csum_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int btrfs_ordered_sum_size(struct btrfs_fs_info *fs_info,
					 unsigned long bytes)
{
	int num_sectors = (int)DIV_ROUND_UP(bytes, fs_info->sectorsize);
	int csum_size = btrfs_super_csum_size(fs_info->super_copy);

	return sizeof(struct btrfs_ordered_sum) + num_sectors * csum_size;
}