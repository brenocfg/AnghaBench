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
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {struct btrfs_root* chunk_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_DATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 int /*<<< orphan*/  get_alloc_profile (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_alloc_profile_by_root(struct btrfs_root *root, int data)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	u64 flags;
	u64 ret;

	if (data)
		flags = BTRFS_BLOCK_GROUP_DATA;
	else if (root == fs_info->chunk_root)
		flags = BTRFS_BLOCK_GROUP_SYSTEM;
	else
		flags = BTRFS_BLOCK_GROUP_METADATA;

	ret = get_alloc_profile(fs_info, flags);
	return ret;
}