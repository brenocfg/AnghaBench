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
struct nfs_open_context {struct cred* cred; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; int /*<<< orphan*/  ia_file; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_FILE ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_OPEN ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nfs4_label*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int PTR_ERR (struct nfs4_label*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int nfs4_do_setattr (struct inode*,struct cred const*,struct nfs_fattr*,struct iattr*,struct nfs_open_context*,int /*<<< orphan*/ *,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs4_inode_make_writeable (struct inode*) ; 
 struct nfs4_label* nfs4_label_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_free (struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 struct nfs_open_context* nfs_file_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_setattr_update_inode (struct inode*,struct iattr*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_setsecurity (struct inode*,struct nfs_fattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  pnfs_commit_and_return_layout (struct inode*) ; 
 scalar_t__ pnfs_ld_layoutret_on_setattr (struct inode*) ; 

__attribute__((used)) static int
nfs4_proc_setattr(struct dentry *dentry, struct nfs_fattr *fattr,
		  struct iattr *sattr)
{
	struct inode *inode = d_inode(dentry);
	const struct cred *cred = NULL;
	struct nfs_open_context *ctx = NULL;
	struct nfs4_label *label = NULL;
	int status;

	if (pnfs_ld_layoutret_on_setattr(inode) &&
	    sattr->ia_valid & ATTR_SIZE &&
	    sattr->ia_size < i_size_read(inode))
		pnfs_commit_and_return_layout(inode);

	nfs_fattr_init(fattr);
	
	/* Deal with open(O_TRUNC) */
	if (sattr->ia_valid & ATTR_OPEN)
		sattr->ia_valid &= ~(ATTR_MTIME|ATTR_CTIME);

	/* Optimization: if the end result is no change, don't RPC */
	if ((sattr->ia_valid & ~(ATTR_FILE|ATTR_OPEN)) == 0)
		return 0;

	/* Search for an existing open(O_WRITE) file */
	if (sattr->ia_valid & ATTR_FILE) {

		ctx = nfs_file_open_context(sattr->ia_file);
		if (ctx)
			cred = ctx->cred;
	}

	label = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	if (IS_ERR(label))
		return PTR_ERR(label);

	/* Return any delegations if we're going to change ACLs */
	if ((sattr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0)
		nfs4_inode_make_writeable(inode);

	status = nfs4_do_setattr(inode, cred, fattr, sattr, ctx, NULL, label);
	if (status == 0) {
		nfs_setattr_update_inode(inode, sattr, fattr);
		nfs_setsecurity(inode, fattr, label);
	}
	nfs4_label_free(label);
	return status;
}