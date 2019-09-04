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
 int __btrfs_qgroup_release_data (struct inode*,struct extent_changeset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int btrfs_qgroup_free_data(struct inode *inode,
			struct extent_changeset *reserved, u64 start, u64 len)
{
	return __btrfs_qgroup_release_data(inode, reserved, start, len, 1);
}