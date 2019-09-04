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
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_opflags; int /*<<< orphan*/ * i_op; scalar_t__ i_blocks; int /*<<< orphan*/  i_blkbits; scalar_t__ i_size; scalar_t__ i_rdev; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  IOP_XATTR ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  empty_dir_inode_operations ; 
 int /*<<< orphan*/  empty_dir_operations ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

void make_empty_dir_inode(struct inode *inode)
{
	set_nlink(inode, 2);
	inode->i_mode = S_IFDIR | S_IRUGO | S_IXUGO;
	inode->i_uid = GLOBAL_ROOT_UID;
	inode->i_gid = GLOBAL_ROOT_GID;
	inode->i_rdev = 0;
	inode->i_size = 0;
	inode->i_blkbits = PAGE_SHIFT;
	inode->i_blocks = 0;

	inode->i_op = &empty_dir_inode_operations;
	inode->i_opflags &= ~IOP_XATTR;
	inode->i_fop = &empty_dir_operations;
}