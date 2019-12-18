#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct extent_changeset {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_4__ {struct btrfs_root* root; } ;
struct TYPE_3__ {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space_noquota (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_data (struct inode*,struct extent_changeset*,scalar_t__,scalar_t__) ; 
 scalar_t__ round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ round_up (scalar_t__,int /*<<< orphan*/ ) ; 

void btrfs_free_reserved_data_space(struct inode *inode,
			struct extent_changeset *reserved, u64 start, u64 len)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;

	/* Make sure the range is aligned to sectorsize */
	len = round_up(start + len, root->fs_info->sectorsize) -
	      round_down(start, root->fs_info->sectorsize);
	start = round_down(start, root->fs_info->sectorsize);

	btrfs_free_reserved_data_space_noquota(inode, start, len);
	btrfs_qgroup_free_data(inode, reserved, start, len);
}