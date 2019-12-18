#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct nfs_server {TYPE_2__* client; TYPE_4__* nfs_client; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_8__ {TYPE_3__* rpc_ops; } ;
struct TYPE_7__ {int (* lookup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__* cl_auth; } ;
struct TYPE_5__ {int /*<<< orphan*/  au_flavor; } ;

/* Variables and functions */
 struct vfsmount* ERR_PTR (int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct vfsmount* nfs_do_submount (struct dentry*,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *) ; 

struct vfsmount *nfs_submount(struct nfs_server *server, struct dentry *dentry,
			      struct nfs_fh *fh, struct nfs_fattr *fattr)
{
	int err;
	struct dentry *parent = dget_parent(dentry);

	/* Look it up again to get its attributes */
	err = server->nfs_client->rpc_ops->lookup(d_inode(parent), &dentry->d_name, fh, fattr, NULL);
	dput(parent);
	if (err != 0)
		return ERR_PTR(err);

	return nfs_do_submount(dentry, fh, fattr, server->client->cl_auth->au_flavor);
}