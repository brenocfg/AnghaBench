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
struct super_block {struct dentry* s_root; } ;
struct pts_mount_opts {int ptmxmode; } ;
struct pts_fs_info {struct dentry* ptmx_dentry; struct pts_mount_opts mount_opts; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 struct pts_fs_info* DEVPTS_SB (struct super_block*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  TTYAUX_MAJOR ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mknod_ptmx(struct super_block *sb)
{
	int mode;
	int rc = -ENOMEM;
	struct dentry *dentry;
	struct inode *inode;
	struct dentry *root = sb->s_root;
	struct pts_fs_info *fsi = DEVPTS_SB(sb);
	struct pts_mount_opts *opts = &fsi->mount_opts;
	kuid_t ptmx_uid = current_fsuid();
	kgid_t ptmx_gid = current_fsgid();

	inode_lock(d_inode(root));

	/* If we have already created ptmx node, return */
	if (fsi->ptmx_dentry) {
		rc = 0;
		goto out;
	}

	dentry = d_alloc_name(root, "ptmx");
	if (!dentry) {
		pr_err("Unable to alloc dentry for ptmx node\n");
		goto out;
	}

	/*
	 * Create a new 'ptmx' node in this mount of devpts.
	 */
	inode = new_inode(sb);
	if (!inode) {
		pr_err("Unable to alloc inode for ptmx node\n");
		dput(dentry);
		goto out;
	}

	inode->i_ino = 2;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);

	mode = S_IFCHR|opts->ptmxmode;
	init_special_inode(inode, mode, MKDEV(TTYAUX_MAJOR, 2));
	inode->i_uid = ptmx_uid;
	inode->i_gid = ptmx_gid;

	d_add(dentry, inode);

	fsi->ptmx_dentry = dentry;
	rc = 0;
out:
	inode_unlock(d_inode(root));
	return rc;
}