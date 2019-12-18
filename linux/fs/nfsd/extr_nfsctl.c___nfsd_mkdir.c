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
typedef  int /*<<< orphan*/  umode_t ;
struct nfsdfs_client {int /*<<< orphan*/  cl_ref; } ;
struct inode {struct nfsdfs_client* i_private; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  fsnotify_mkdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct inode* nfsd_get_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nfsd_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode, struct nfsdfs_client *ncl)
{
	struct inode *inode;

	inode = nfsd_get_inode(dir->i_sb, mode);
	if (!inode)
		return -ENOMEM;
	if (ncl) {
		inode->i_private = ncl;
		kref_get(&ncl->cl_ref);
	}
	d_add(dentry, inode);
	inc_nlink(dir);
	fsnotify_mkdir(dir, dentry);
	return 0;
}