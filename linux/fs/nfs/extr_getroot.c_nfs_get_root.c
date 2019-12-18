#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_fsinfo {int /*<<< orphan*/ * fattr; } ;
struct nfs_fh {int dummy; } ;
struct inode {int d_flags; int /*<<< orphan*/  d_lock; void* d_fsdata; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; void* d_fsdata; } ;
struct TYPE_4__ {TYPE_1__* rpc_ops; } ;
struct TYPE_3__ {int (* getroot ) (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ;} ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int ENOMEM ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ IS_ROOT (struct inode*) ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 struct inode* d_obtain_root (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 struct inode* nfs_fhget (struct super_block*,struct nfs_fh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int nfs_superblock_set_dummy_root (struct super_block*,struct inode*) ; 
 int /*<<< orphan*/  security_d_instantiate (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 

struct dentry *nfs_get_root(struct super_block *sb, struct nfs_fh *mntfh,
			    const char *devname)
{
	struct nfs_server *server = NFS_SB(sb);
	struct nfs_fsinfo fsinfo;
	struct dentry *ret;
	struct inode *inode;
	void *name = kstrdup(devname, GFP_KERNEL);
	int error;

	if (!name)
		return ERR_PTR(-ENOMEM);

	/* get the actual root for this mount */
	fsinfo.fattr = nfs_alloc_fattr();
	if (fsinfo.fattr == NULL) {
		kfree(name);
		return ERR_PTR(-ENOMEM);
	}

	error = server->nfs_client->rpc_ops->getroot(server, mntfh, &fsinfo);
	if (error < 0) {
		dprintk("nfs_get_root: getattr error = %d\n", -error);
		ret = ERR_PTR(error);
		goto out;
	}

	inode = nfs_fhget(sb, mntfh, fsinfo.fattr, NULL);
	if (IS_ERR(inode)) {
		dprintk("nfs_get_root: get root inode failed\n");
		ret = ERR_CAST(inode);
		goto out;
	}

	error = nfs_superblock_set_dummy_root(sb, inode);
	if (error != 0) {
		ret = ERR_PTR(error);
		goto out;
	}

	/* root dentries normally start off anonymous and get spliced in later
	 * if the dentry tree reaches them; however if the dentry already
	 * exists, we'll pick it up at this point and use it as the root
	 */
	ret = d_obtain_root(inode);
	if (IS_ERR(ret)) {
		dprintk("nfs_get_root: get root dentry failed\n");
		goto out;
	}

	security_d_instantiate(ret, inode);
	spin_lock(&ret->d_lock);
	if (IS_ROOT(ret) && !ret->d_fsdata &&
	    !(ret->d_flags & DCACHE_NFSFS_RENAMED)) {
		ret->d_fsdata = name;
		name = NULL;
	}
	spin_unlock(&ret->d_lock);
out:
	kfree(name);
	nfs_free_fattr(fsinfo.fattr);
	return ret;
}