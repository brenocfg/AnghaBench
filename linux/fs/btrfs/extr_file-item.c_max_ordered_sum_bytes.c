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
typedef  int u32 ;
typedef  int u16 ;
struct btrfs_ordered_sum {int dummy; } ;
struct btrfs_fs_info {int sectorsize; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static inline u32 max_ordered_sum_bytes(struct btrfs_fs_info *fs_info,
					u16 csum_size)
{
	u32 ncsums = (PAGE_SIZE - sizeof(struct btrfs_ordered_sum)) / csum_size;

	return ncsums * fs_info->sectorsize;
}