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
struct inode {void* i_private; int /*<<< orphan*/  i_flags; } ;
struct dentry {int /*<<< orphan*/  d_parent; void* d_fsdata; int /*<<< orphan*/  d_sb; } ;
typedef  scalar_t__ debugfs_automount_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_AUTOMOUNT ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 struct inode* debugfs_get_inode (int /*<<< orphan*/ ) ; 
 struct dentry* end_creating (struct dentry*) ; 
 struct dentry* failed_creating (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_mkdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  make_empty_dir_inode (struct inode*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct dentry* start_creating (char const*,struct dentry*) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *debugfs_create_automount(const char *name,
					struct dentry *parent,
					debugfs_automount_t f,
					void *data)
{
	struct dentry *dentry = start_creating(name, parent);
	struct inode *inode;

	if (IS_ERR(dentry))
		return dentry;

	inode = debugfs_get_inode(dentry->d_sb);
	if (unlikely(!inode)) {
		pr_err("out of free dentries, can not create automount '%s'\n",
		       name);
		return failed_creating(dentry);
	}

	make_empty_dir_inode(inode);
	inode->i_flags |= S_AUTOMOUNT;
	inode->i_private = data;
	dentry->d_fsdata = (void *)f;
	/* directory inodes start off with i_nlink == 2 (for "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	inc_nlink(d_inode(dentry->d_parent));
	fsnotify_mkdir(d_inode(dentry->d_parent), dentry);
	return end_creating(dentry);
}