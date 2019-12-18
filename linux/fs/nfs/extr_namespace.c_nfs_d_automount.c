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
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* rpc_ops; } ;
struct TYPE_3__ {struct vfsmount* (* submount ) (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fh*,struct nfs_fattr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 scalar_t__ IS_ROOT (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_set_expiry (struct vfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 struct nfs_fh* nfs_alloc_fhandle () ; 
 int /*<<< orphan*/  nfs_automount_list ; 
 int /*<<< orphan*/  nfs_automount_task ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_fhandle (struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_mountpoint_expiry_timeout ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vfsmount* stub1 (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fh*,struct nfs_fattr*) ; 

struct vfsmount *nfs_d_automount(struct path *path)
{
	struct vfsmount *mnt;
	struct nfs_server *server = NFS_SERVER(d_inode(path->dentry));
	struct nfs_fh *fh = NULL;
	struct nfs_fattr *fattr = NULL;

	if (IS_ROOT(path->dentry))
		return ERR_PTR(-ESTALE);

	mnt = ERR_PTR(-ENOMEM);
	fh = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	if (fh == NULL || fattr == NULL)
		goto out;

	mnt = server->nfs_client->rpc_ops->submount(server, path->dentry, fh, fattr);
	if (IS_ERR(mnt))
		goto out;

	mntget(mnt); /* prevent immediate expiration */
	mnt_set_expiry(mnt, &nfs_automount_list);
	schedule_delayed_work(&nfs_automount_task, nfs_mountpoint_expiry_timeout);

out:
	nfs_free_fattr(fattr);
	nfs_free_fhandle(fh);
	return mnt;
}