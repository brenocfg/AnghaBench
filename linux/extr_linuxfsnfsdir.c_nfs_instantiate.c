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
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_fh {scalar_t__ size; } ;
struct nfs_fattr {int valid; } ;
struct nfs4_label {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_name; } ;
struct TYPE_6__ {int (* lookup ) (struct inode*,int /*<<< orphan*/ *,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__* rpc_ops; } ;
struct TYPE_4__ {int (* getattr ) (struct nfs_server*,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int NFS_ATTR_FATTR ; 
 TYPE_3__* NFS_PROTO (struct inode*) ; 
 struct nfs_server* NFS_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* nfs_fhget (int /*<<< orphan*/ ,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ *,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *) ; 
 int stub2 (struct nfs_server*,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nfs_instantiate(struct dentry *dentry, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr,
				struct nfs4_label *label)
{
	struct dentry *parent = dget_parent(dentry);
	struct inode *dir = d_inode(parent);
	struct inode *inode;
	struct dentry *d;
	int error = -EACCES;

	d_drop(dentry);

	/* We may have been initialized further down */
	if (d_really_is_positive(dentry))
		goto out;
	if (fhandle->size == 0) {
		error = NFS_PROTO(dir)->lookup(dir, &dentry->d_name, fhandle, fattr, NULL);
		if (error)
			goto out_error;
	}
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	if (!(fattr->valid & NFS_ATTR_FATTR)) {
		struct nfs_server *server = NFS_SB(dentry->d_sb);
		error = server->nfs_client->rpc_ops->getattr(server, fhandle,
				fattr, NULL, NULL);
		if (error < 0)
			goto out_error;
	}
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr, label);
	d = d_splice_alias(inode, dentry);
	if (IS_ERR(d)) {
		error = PTR_ERR(d);
		goto out_error;
	}
	dput(d);
out:
	dput(parent);
	return 0;
out_error:
	nfs_mark_for_revalidate(dir);
	dput(parent);
	return error;
}