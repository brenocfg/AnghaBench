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

/* Variables and functions */
 int BTRFS_SUPER_INFO_OFFSET ; 
 int BTRFS_SUPER_MIRROR_SHIFT ; 
 int SZ_16K ; 

__attribute__((used)) static inline u64 btrfs_sb_offset(int mirror)
{
	u64 start = SZ_16K;
	if (mirror)
		return start << (BTRFS_SUPER_MIRROR_SHIFT * mirror);
	return BTRFS_SUPER_INFO_OFFSET;
}