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
struct inode {unsigned long i_ino; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 struct inode* sel_make_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static struct dentry *sel_make_dir(struct dentry *dir, const char *name,
			unsigned long *ino)
{
	struct dentry *dentry = d_alloc_name(dir, name);
	struct inode *inode;

	if (!dentry)
		return ERR_PTR(-ENOMEM);

	inode = sel_make_inode(dir->d_sb, S_IFDIR | S_IRUGO | S_IXUGO);
	if (!inode) {
		dput(dentry);
		return ERR_PTR(-ENOMEM);
	}

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	inode->i_ino = ++(*ino);
	/* directory inodes start off with i_nlink == 2 (for "." entry) */
	inc_nlink(inode);
	d_add(dentry, inode);
	/* bump link count on parent directory, too */
	inc_nlink(d_inode(dir));

	return dentry;
}