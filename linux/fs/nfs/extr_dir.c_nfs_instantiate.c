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
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* nfs_add_or_obtain (struct dentry*,struct nfs_fh*,struct nfs_fattr*,struct nfs4_label*) ; 

int nfs_instantiate(struct dentry *dentry, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr,
				struct nfs4_label *label)
{
	struct dentry *d;

	d = nfs_add_or_obtain(dentry, fhandle, fattr, label);
	if (IS_ERR(d))
		return PTR_ERR(d);

	/* Callers don't care */
	dput(d);
	return 0;
}