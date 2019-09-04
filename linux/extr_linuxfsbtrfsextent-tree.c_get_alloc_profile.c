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
struct btrfs_fs_info {int avail_data_alloc_bits; int avail_system_alloc_bits; int avail_metadata_alloc_bits; int /*<<< orphan*/  profiles_lock; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int BTRFS_BLOCK_GROUP_SYSTEM ; 
 int btrfs_reduce_alloc_profile (struct btrfs_fs_info*,int) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static u64 get_alloc_profile(struct btrfs_fs_info *fs_info, u64 orig_flags)
{
	unsigned seq;
	u64 flags;

	do {
		flags = orig_flags;
		seq = read_seqbegin(&fs_info->profiles_lock);

		if (flags & BTRFS_BLOCK_GROUP_DATA)
			flags |= fs_info->avail_data_alloc_bits;
		else if (flags & BTRFS_BLOCK_GROUP_SYSTEM)
			flags |= fs_info->avail_system_alloc_bits;
		else if (flags & BTRFS_BLOCK_GROUP_METADATA)
			flags |= fs_info->avail_metadata_alloc_bits;
	} while (read_seqretry(&fs_info->profiles_lock, seq));

	return btrfs_reduce_alloc_profile(fs_info, flags);
}