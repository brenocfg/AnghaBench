#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {scalar_t__ mnt; } ;
struct svc_export {int ex_flags; TYPE_1__ ex_path; } ;
struct path {scalar_t__ mnt; struct dentry* dentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ EX_NOHIDE (struct svc_export*) ; 
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int NFSEXP_CROSSMOUNT ; 
 int NFSEXP_V4ROOT ; 
 int PTR_ERR (struct svc_export*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 int follow_down (struct path*) ; 
 scalar_t__ mntget (scalar_t__) ; 
 int nfsd_mountpoint (struct dentry*,struct svc_export*) ; 
 scalar_t__ nfsd_v4client (struct svc_rqst*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 struct svc_export* rqst_exp_get_by_name (struct svc_rqst*,struct path*) ; 

int
nfsd_cross_mnt(struct svc_rqst *rqstp, struct dentry **dpp, 
		        struct svc_export **expp)
{
	struct svc_export *exp = *expp, *exp2 = NULL;
	struct dentry *dentry = *dpp;
	struct path path = {.mnt = mntget(exp->ex_path.mnt),
			    .dentry = dget(dentry)};
	int err = 0;

	err = follow_down(&path);
	if (err < 0)
		goto out;
	if (path.mnt == exp->ex_path.mnt && path.dentry == dentry &&
	    nfsd_mountpoint(dentry, exp) == 2) {
		/* This is only a mountpoint in some other namespace */
		path_put(&path);
		goto out;
	}

	exp2 = rqst_exp_get_by_name(rqstp, &path);
	if (IS_ERR(exp2)) {
		err = PTR_ERR(exp2);
		/*
		 * We normally allow NFS clients to continue
		 * "underneath" a mountpoint that is not exported.
		 * The exception is V4ROOT, where no traversal is ever
		 * allowed without an explicit export of the new
		 * directory.
		 */
		if (err == -ENOENT && !(exp->ex_flags & NFSEXP_V4ROOT))
			err = 0;
		path_put(&path);
		goto out;
	}
	if (nfsd_v4client(rqstp) ||
		(exp->ex_flags & NFSEXP_CROSSMOUNT) || EX_NOHIDE(exp2)) {
		/* successfully crossed mount point */
		/*
		 * This is subtle: path.dentry is *not* on path.mnt
		 * at this point.  The only reason we are safe is that
		 * original mnt is pinned down by exp, so we should
		 * put path *before* putting exp
		 */
		*dpp = path.dentry;
		path.dentry = dentry;
		*expp = exp2;
		exp2 = exp;
	}
	path_put(&path);
	exp_put(exp2);
out:
	return err;
}