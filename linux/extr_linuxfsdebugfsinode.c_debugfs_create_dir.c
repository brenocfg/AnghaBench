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
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 struct inode* debugfs_get_inode (int /*<<< orphan*/ ) ; 
 struct dentry* end_creating (struct dentry*) ; 
 struct dentry* failed_creating (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_mkdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 struct dentry* start_creating (char const*,struct dentry*) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *debugfs_create_dir(const char *name, struct dentry *parent)
{
	struct dentry *dentry = start_creating(name, parent);
	struct inode *inode;

	if (IS_ERR(dentry))
		return NULL;

	inode = debugfs_get_inode(dentry->d_sb);
	if (unlikely(!inode))
		return failed_creating(dentry);

	inode->i_mode = S_IFDIR | S_IRWXU | S_IRUGO | S_IXUGO;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	/* directory inodes start off with i_nlink == 2 (for "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	inc_nlink(d_inode(dentry->d_parent));
	fsnotify_mkdir(d_inode(dentry->d_parent), dentry);
	return end_creating(dentry);
}