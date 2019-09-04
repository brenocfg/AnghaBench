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
struct inode {int dummy; } ;
struct extent_changeset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int btrfs_check_data_free_space (struct inode*,struct extent_changeset**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_delalloc_reserve_metadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space (struct inode*,struct extent_changeset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_delalloc_reserve_space(struct inode *inode,
			struct extent_changeset **reserved, u64 start, u64 len)
{
	int ret;

	ret = btrfs_check_data_free_space(inode, reserved, start, len);
	if (ret < 0)
		return ret;
	ret = btrfs_delalloc_reserve_metadata(BTRFS_I(inode), len);
	if (ret < 0)
		btrfs_free_reserved_data_space(inode, *reserved, start, len);
	return ret;
}