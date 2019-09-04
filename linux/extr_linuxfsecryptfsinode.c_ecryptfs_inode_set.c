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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_aops ; 
 int /*<<< orphan*/  ecryptfs_dir_fops ; 
 int /*<<< orphan*/  ecryptfs_dir_iops ; 
 int /*<<< orphan*/  ecryptfs_main_fops ; 
 int /*<<< orphan*/  ecryptfs_main_iops ; 
 int /*<<< orphan*/  ecryptfs_set_inode_lower (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ecryptfs_symlink_iops ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  fsstack_copy_inode_size (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ special_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_inode_set(struct inode *inode, void *opaque)
{
	struct inode *lower_inode = opaque;

	ecryptfs_set_inode_lower(inode, lower_inode);
	fsstack_copy_attr_all(inode, lower_inode);
	/* i_size will be overwritten for encrypted regular files */
	fsstack_copy_inode_size(inode, lower_inode);
	inode->i_ino = lower_inode->i_ino;
	inode->i_mapping->a_ops = &ecryptfs_aops;

	if (S_ISLNK(inode->i_mode))
		inode->i_op = &ecryptfs_symlink_iops;
	else if (S_ISDIR(inode->i_mode))
		inode->i_op = &ecryptfs_dir_iops;
	else
		inode->i_op = &ecryptfs_main_iops;

	if (S_ISDIR(inode->i_mode))
		inode->i_fop = &ecryptfs_dir_fops;
	else if (special_file(inode->i_mode))
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	else
		inode->i_fop = &ecryptfs_main_fops;

	return 0;
}