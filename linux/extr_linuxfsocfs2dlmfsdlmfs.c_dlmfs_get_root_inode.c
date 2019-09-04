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
typedef  int umode_t ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dlmfs_root_inode_operations ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,int /*<<< orphan*/ *,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static struct inode *dlmfs_get_root_inode(struct super_block *sb)
{
	struct inode *inode = new_inode(sb);
	umode_t mode = S_IFDIR | 0755;

	if (inode) {
		inode->i_ino = get_next_ino();
		inode_init_owner(inode, NULL, mode);
		inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
		inc_nlink(inode);

		inode->i_fop = &simple_dir_operations;
		inode->i_op = &dlmfs_root_inode_operations;
	}

	return inode;
}