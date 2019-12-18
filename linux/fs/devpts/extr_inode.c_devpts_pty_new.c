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
struct pts_mount_opts {int mode; int /*<<< orphan*/  gid; scalar_t__ setgid; int /*<<< orphan*/  uid; scalar_t__ setuid; } ;
struct pts_fs_info {struct pts_mount_opts mount_opts; struct super_block* sb; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {void* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  UNIX98_PTY_SLAVE_MAJOR ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_create (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

struct dentry *devpts_pty_new(struct pts_fs_info *fsi, int index, void *priv)
{
	struct dentry *dentry;
	struct super_block *sb = fsi->sb;
	struct inode *inode;
	struct dentry *root;
	struct pts_mount_opts *opts;
	char s[12];

	root = sb->s_root;
	opts = &fsi->mount_opts;

	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	inode->i_ino = index + 3;
	inode->i_uid = opts->setuid ? opts->uid : current_fsuid();
	inode->i_gid = opts->setgid ? opts->gid : current_fsgid();
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	init_special_inode(inode, S_IFCHR|opts->mode, MKDEV(UNIX98_PTY_SLAVE_MAJOR, index));

	sprintf(s, "%d", index);

	dentry = d_alloc_name(root, s);
	if (dentry) {
		dentry->d_fsdata = priv;
		d_add(dentry, inode);
		fsnotify_create(d_inode(root), dentry);
	} else {
		iput(inode);
		dentry = ERR_PTR(-ENOMEM);
	}

	return dentry;
}