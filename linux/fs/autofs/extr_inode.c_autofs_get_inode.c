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
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {scalar_t__ s_root; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  autofs_dir_inode_operations ; 
 int /*<<< orphan*/  autofs_dir_operations ; 
 int /*<<< orphan*/  autofs_symlink_inode_operations ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 TYPE_1__* d_inode (scalar_t__) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

struct inode *autofs_get_inode(struct super_block *sb, umode_t mode)
{
	struct inode *inode = new_inode(sb);

	if (inode == NULL)
		return NULL;

	inode->i_mode = mode;
	if (sb->s_root) {
		inode->i_uid = d_inode(sb->s_root)->i_uid;
		inode->i_gid = d_inode(sb->s_root)->i_gid;
	}
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	inode->i_ino = get_next_ino();

	if (S_ISDIR(mode)) {
		set_nlink(inode, 2);
		inode->i_op = &autofs_dir_inode_operations;
		inode->i_fop = &autofs_dir_operations;
	} else if (S_ISLNK(mode)) {
		inode->i_op = &autofs_symlink_inode_operations;
	} else
		WARN_ON(1);

	return inode;
}