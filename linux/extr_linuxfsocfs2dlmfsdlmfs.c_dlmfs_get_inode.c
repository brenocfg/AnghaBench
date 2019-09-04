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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct dlmfs_inode_private {int /*<<< orphan*/  ip_parent; int /*<<< orphan*/  ip_lockres; int /*<<< orphan*/  ip_conn; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int /*<<< orphan*/  DLM_LVB_LEN ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dlmfs_dir_inode_operations ; 
 int /*<<< orphan*/  dlmfs_file_inode_operations ; 
 int /*<<< orphan*/  dlmfs_file_operations ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  user_dlm_lock_res_init (int /*<<< orphan*/ *,struct dentry*) ; 

__attribute__((used)) static struct inode *dlmfs_get_inode(struct inode *parent,
				     struct dentry *dentry,
				     umode_t mode)
{
	struct super_block *sb = parent->i_sb;
	struct inode * inode = new_inode(sb);
	struct dlmfs_inode_private *ip;

	if (!inode)
		return NULL;

	inode->i_ino = get_next_ino();
	inode_init_owner(inode, parent, mode);
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);

	ip = DLMFS_I(inode);
	ip->ip_conn = DLMFS_I(parent)->ip_conn;

	switch (mode & S_IFMT) {
	default:
		/* for now we don't support anything other than
		 * directories and regular files. */
		BUG();
		break;
	case S_IFREG:
		inode->i_op = &dlmfs_file_inode_operations;
		inode->i_fop = &dlmfs_file_operations;

		i_size_write(inode,  DLM_LVB_LEN);

		user_dlm_lock_res_init(&ip->ip_lockres, dentry);

		/* released at clear_inode time, this insures that we
		 * get to drop the dlm reference on each lock *before*
		 * we call the unregister code for releasing parent
		 * directories. */
		ip->ip_parent = igrab(parent);
		BUG_ON(!ip->ip_parent);
		break;
	case S_IFDIR:
		inode->i_op = &dlmfs_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;

		/* directory inodes start off with i_nlink ==
		 * 2 (for "." entry) */
		inc_nlink(inode);
		break;
	}
	return inode;
}