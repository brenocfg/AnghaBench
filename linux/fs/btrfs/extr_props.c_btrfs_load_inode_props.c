#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct TYPE_3__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_1__*) ; 
 int /*<<< orphan*/  inode_prop_iterator ; 
 int iterate_object_props (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 

int btrfs_load_inode_props(struct inode *inode, struct btrfs_path *path)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	u64 ino = btrfs_ino(BTRFS_I(inode));
	int ret;

	ret = iterate_object_props(root, path, ino, inode_prop_iterator, inode);

	return ret;
}