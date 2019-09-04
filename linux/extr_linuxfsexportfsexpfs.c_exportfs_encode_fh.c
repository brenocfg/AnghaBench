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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct fid {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int exportfs_encode_inode_fh (struct inode*,struct fid*,int*,struct inode*) ; 

int exportfs_encode_fh(struct dentry *dentry, struct fid *fid, int *max_len,
		int connectable)
{
	int error;
	struct dentry *p = NULL;
	struct inode *inode = dentry->d_inode, *parent = NULL;

	if (connectable && !S_ISDIR(inode->i_mode)) {
		p = dget_parent(dentry);
		/*
		 * note that while p might've ceased to be our parent already,
		 * it's still pinned by and still positive.
		 */
		parent = p->d_inode;
	}

	error = exportfs_encode_inode_fh(inode, fid, max_len, parent);
	dput(p);

	return error;
}