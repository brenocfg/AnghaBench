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
 int /*<<< orphan*/  btrfs_delalloc_release_metadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space (struct inode*,struct extent_changeset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btrfs_delalloc_release_space(struct inode *inode,
				  struct extent_changeset *reserved,
				  u64 start, u64 len, bool qgroup_free)
{
	btrfs_delalloc_release_metadata(BTRFS_I(inode), len, qgroup_free);
	btrfs_free_reserved_data_space(inode, reserved, start, len);
}