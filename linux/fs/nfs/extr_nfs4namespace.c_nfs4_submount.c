#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct rpc_clnt {TYPE_1__* cl_auth; } ;
struct qstr {int dummy; } ;
struct nfs_server {TYPE_3__* client; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int valid; } ;
struct inode {int dummy; } ;
struct dentry {struct qstr d_name; } ;
typedef  scalar_t__ rpc_authflavor_t ;
struct TYPE_6__ {TYPE_2__* cl_auth; } ;
struct TYPE_5__ {scalar_t__ au_flavor; } ;
struct TYPE_4__ {scalar_t__ au_flavor; } ;

/* Variables and functions */
 struct vfsmount* ERR_CAST (struct rpc_clnt*) ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 int NFS_ATTR_FATTR_V4_REFERRAL ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct rpc_clnt* nfs4_proc_lookup_mountpoint (struct inode*,struct qstr const*,struct nfs_fh*,struct nfs_fattr*) ; 
 struct vfsmount* nfs_do_refmount (struct rpc_clnt*,struct dentry*) ; 
 struct vfsmount* nfs_do_submount (struct dentry*,struct nfs_fh*,struct nfs_fattr*,scalar_t__) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

struct vfsmount *nfs4_submount(struct nfs_server *server, struct dentry *dentry,
			       struct nfs_fh *fh, struct nfs_fattr *fattr)
{
	rpc_authflavor_t flavor = server->client->cl_auth->au_flavor;
	struct dentry *parent = dget_parent(dentry);
	struct inode *dir = d_inode(parent);
	const struct qstr *name = &dentry->d_name;
	struct rpc_clnt *client;
	struct vfsmount *mnt;

	/* Look it up again to get its attributes and sec flavor */
	client = nfs4_proc_lookup_mountpoint(dir, name, fh, fattr);
	dput(parent);
	if (IS_ERR(client))
		return ERR_CAST(client);

	if (fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) {
		mnt = nfs_do_refmount(client, dentry);
		goto out;
	}

	if (client->cl_auth->au_flavor != flavor)
		flavor = client->cl_auth->au_flavor;
	mnt = nfs_do_submount(dentry, fh, fattr, flavor);
out:
	rpc_shutdown_client(client);
	return mnt;
}