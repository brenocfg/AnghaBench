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
struct nfsdfs_client {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 int S_IFDIR ; 
 int __nfsd_mkdir (int /*<<< orphan*/ ,struct dentry*,int,struct nfsdfs_client*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static struct dentry *nfsd_mkdir(struct dentry *parent, struct nfsdfs_client *ncl, char *name)
{
	struct inode *dir = parent->d_inode;
	struct dentry *dentry;
	int ret = -ENOMEM;

	inode_lock(dir);
	dentry = d_alloc_name(parent, name);
	if (!dentry)
		goto out_err;
	ret = __nfsd_mkdir(d_inode(parent), dentry, S_IFDIR | 0600, ncl);
	if (ret)
		goto out_err;
out:
	inode_unlock(dir);
	return dentry;
out_err:
	dput(dentry);
	dentry = ERR_PTR(ret);
	goto out;
}