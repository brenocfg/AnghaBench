#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {char* i_link; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; TYPE_2__* i_mapping; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/ * i_fop; } ;
struct TYPE_5__ {scalar_t__ i_symlink; } ;
struct TYPE_7__ {TYPE_1__ i_u1; } ;
struct TYPE_6__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_3__* UFS_I (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  simple_symlink_inode_operations ; 
 int /*<<< orphan*/  ufs_aops ; 
 int /*<<< orphan*/  ufs_dir_inode_operations ; 
 int /*<<< orphan*/  ufs_dir_operations ; 
 int /*<<< orphan*/  ufs_file_inode_operations ; 
 int /*<<< orphan*/  ufs_file_operations ; 
 int /*<<< orphan*/  ufs_get_inode_dev (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void ufs_set_inode_ops(struct inode *inode)
{
	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &ufs_file_inode_operations;
		inode->i_fop = &ufs_file_operations;
		inode->i_mapping->a_ops = &ufs_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &ufs_dir_inode_operations;
		inode->i_fop = &ufs_dir_operations;
		inode->i_mapping->a_ops = &ufs_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		if (!inode->i_blocks) {
			inode->i_link = (char *)UFS_I(inode)->i_u1.i_symlink;
			inode->i_op = &simple_symlink_inode_operations;
		} else {
			inode->i_mapping->a_ops = &ufs_aops;
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
		}
	} else
		init_special_inode(inode, inode->i_mode,
				   ufs_get_inode_dev(inode->i_sb, UFS_I(inode)));
}