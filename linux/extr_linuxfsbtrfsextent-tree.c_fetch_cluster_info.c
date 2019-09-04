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
typedef  scalar_t__ u64 ;
struct btrfs_space_info {int flags; } ;
struct btrfs_free_cluster {int dummy; } ;
struct btrfs_fs_info {struct btrfs_free_cluster data_alloc_cluster; struct btrfs_free_cluster meta_alloc_cluster; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  SSD ; 
 int /*<<< orphan*/  SSD_SPREAD ; 
 scalar_t__ SZ_2M ; 
 scalar_t__ SZ_64K ; 
 scalar_t__ btrfs_mixed_space_info (struct btrfs_space_info*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct btrfs_free_cluster *
fetch_cluster_info(struct btrfs_fs_info *fs_info,
		   struct btrfs_space_info *space_info, u64 *empty_cluster)
{
	struct btrfs_free_cluster *ret = NULL;

	*empty_cluster = 0;
	if (btrfs_mixed_space_info(space_info))
		return ret;

	if (space_info->flags & BTRFS_BLOCK_GROUP_METADATA) {
		ret = &fs_info->meta_alloc_cluster;
		if (btrfs_test_opt(fs_info, SSD))
			*empty_cluster = SZ_2M;
		else
			*empty_cluster = SZ_64K;
	} else if ((space_info->flags & BTRFS_BLOCK_GROUP_DATA) &&
		   btrfs_test_opt(fs_info, SSD_SPREAD)) {
		*empty_cluster = SZ_2M;
		ret = &fs_info->data_alloc_cluster;
	}

	return ret;
}