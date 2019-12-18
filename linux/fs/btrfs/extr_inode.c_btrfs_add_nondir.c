#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_inode {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int btrfs_add_link (struct btrfs_trans_handle*,struct btrfs_inode*,struct btrfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_add_nondir(struct btrfs_trans_handle *trans,
			    struct btrfs_inode *dir, struct dentry *dentry,
			    struct btrfs_inode *inode, int backref, u64 index)
{
	int err = btrfs_add_link(trans, dir, inode,
				 dentry->d_name.name, dentry->d_name.len,
				 backref, index);
	if (err > 0)
		err = -EEXIST;
	return err;
}