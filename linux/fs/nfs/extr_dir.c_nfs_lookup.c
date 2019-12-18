#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct nfs4_label {int /*<<< orphan*/  d_sb; TYPE_1__ d_name; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_1__ d_name; } ;
struct TYPE_7__ {int (* lookup ) (struct inode*,TYPE_1__*,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*) ;} ;
struct TYPE_6__ {scalar_t__ namelen; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct nfs4_label* ERR_CAST (struct inode*) ; 
 struct nfs4_label* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ IS_ERR (struct nfs4_label*) ; 
 unsigned int LOOKUP_RENAME_TARGET ; 
 int /*<<< orphan*/  NFSIOS_VFSLOOKUP ; 
 TYPE_4__* NFS_PROTO (struct inode*) ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  VFS ; 
 struct nfs4_label* d_splice_alias (struct inode*,struct nfs4_label*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs4_label*) ; 
 struct nfs4_label* nfs4_label_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_free (struct nfs4_label*) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 struct nfs_fh* nfs_alloc_fhandle () ; 
 struct inode* nfs_fhget (int /*<<< orphan*/ ,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs_force_use_readdirplus (struct inode*) ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_fhandle (struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_is_exclusive_create (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct nfs4_label*,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,TYPE_1__*,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  trace_nfs_lookup_enter (struct inode*,struct nfs4_label*,unsigned int) ; 
 int /*<<< orphan*/  trace_nfs_lookup_exit (struct inode*,struct nfs4_label*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *nfs_lookup(struct inode *dir, struct dentry * dentry, unsigned int flags)
{
	struct dentry *res;
	struct inode *inode = NULL;
	struct nfs_fh *fhandle = NULL;
	struct nfs_fattr *fattr = NULL;
	struct nfs4_label *label = NULL;
	int error;

	dfprintk(VFS, "NFS: lookup(%pd2)\n", dentry);
	nfs_inc_stats(dir, NFSIOS_VFSLOOKUP);

	if (unlikely(dentry->d_name.len > NFS_SERVER(dir)->namelen))
		return ERR_PTR(-ENAMETOOLONG);

	/*
	 * If we're doing an exclusive create, optimize away the lookup
	 * but don't hash the dentry.
	 */
	if (nfs_is_exclusive_create(dir, flags) || flags & LOOKUP_RENAME_TARGET)
		return NULL;

	res = ERR_PTR(-ENOMEM);
	fhandle = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	if (fhandle == NULL || fattr == NULL)
		goto out;

	label = nfs4_label_alloc(NFS_SERVER(dir), GFP_NOWAIT);
	if (IS_ERR(label))
		goto out;

	trace_nfs_lookup_enter(dir, dentry, flags);
	error = NFS_PROTO(dir)->lookup(dir, &dentry->d_name, fhandle, fattr, label);
	if (error == -ENOENT)
		goto no_entry;
	if (error < 0) {
		res = ERR_PTR(error);
		goto out_label;
	}
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr, label);
	res = ERR_CAST(inode);
	if (IS_ERR(res))
		goto out_label;

	/* Notify readdir to use READDIRPLUS */
	nfs_force_use_readdirplus(dir);

no_entry:
	res = d_splice_alias(inode, dentry);
	if (res != NULL) {
		if (IS_ERR(res))
			goto out_label;
		dentry = res;
	}
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
out_label:
	trace_nfs_lookup_exit(dir, dentry, flags, error);
	nfs4_label_free(label);
out:
	nfs_free_fattr(fattr);
	nfs_free_fhandle(fhandle);
	return res;
}