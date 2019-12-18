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
typedef  int u64 ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 int div64_u64 (int,int) ; 

__attribute__((used)) static inline u64 calc_reclaim_items_nr(struct btrfs_fs_info *fs_info,
					u64 to_reclaim)
{
	u64 bytes;
	u64 nr;

	bytes = btrfs_calc_insert_metadata_size(fs_info, 1);
	nr = div64_u64(to_reclaim, bytes);
	if (!nr)
		nr = 1;
	return nr;
}