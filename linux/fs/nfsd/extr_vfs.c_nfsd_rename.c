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
struct svc_rqst {int dummy; } ;
struct svc_fh {int fh_locked; TYPE_2__* fh_export; struct dentry* fh_dentry; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {scalar_t__ mnt; scalar_t__ dentry; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int EXDEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  NFSD_MAY_CREATE ; 
 int /*<<< orphan*/  NFSD_MAY_REMOVE ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int commit_metadata (struct svc_fh*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fh_want_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fill_post_wcc (struct svc_fh*) ; 
 int /*<<< orphan*/  fill_pre_wcc (struct svc_fh*) ; 
 scalar_t__ isdotent (char*,int) ; 
 struct dentry* lock_rename (struct dentry*,struct dentry*) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int /*<<< orphan*/  nfsd_close_cached_files (struct dentry*) ; 
 scalar_t__ nfsd_has_cached_files (struct dentry*) ; 
 scalar_t__ nfserr_perm ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 
 int vfs_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__be32
nfsd_rename(struct svc_rqst *rqstp, struct svc_fh *ffhp, char *fname, int flen,
			    struct svc_fh *tfhp, char *tname, int tlen)
{
	struct dentry	*fdentry, *tdentry, *odentry, *ndentry, *trap;
	struct inode	*fdir, *tdir;
	__be32		err;
	int		host_err;
	bool		has_cached = false;

	err = fh_verify(rqstp, ffhp, S_IFDIR, NFSD_MAY_REMOVE);
	if (err)
		goto out;
	err = fh_verify(rqstp, tfhp, S_IFDIR, NFSD_MAY_CREATE);
	if (err)
		goto out;

	fdentry = ffhp->fh_dentry;
	fdir = d_inode(fdentry);

	tdentry = tfhp->fh_dentry;
	tdir = d_inode(tdentry);

	err = nfserr_perm;
	if (!flen || isdotent(fname, flen) || !tlen || isdotent(tname, tlen))
		goto out;

retry:
	host_err = fh_want_write(ffhp);
	if (host_err) {
		err = nfserrno(host_err);
		goto out;
	}

	/* cannot use fh_lock as we need deadlock protective ordering
	 * so do it by hand */
	trap = lock_rename(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = true;
	fill_pre_wcc(ffhp);
	fill_pre_wcc(tfhp);

	odentry = lookup_one_len(fname, fdentry, flen);
	host_err = PTR_ERR(odentry);
	if (IS_ERR(odentry))
		goto out_nfserr;

	host_err = -ENOENT;
	if (d_really_is_negative(odentry))
		goto out_dput_old;
	host_err = -EINVAL;
	if (odentry == trap)
		goto out_dput_old;

	ndentry = lookup_one_len(tname, tdentry, tlen);
	host_err = PTR_ERR(ndentry);
	if (IS_ERR(ndentry))
		goto out_dput_old;
	host_err = -ENOTEMPTY;
	if (ndentry == trap)
		goto out_dput_new;

	host_err = -EXDEV;
	if (ffhp->fh_export->ex_path.mnt != tfhp->fh_export->ex_path.mnt)
		goto out_dput_new;
	if (ffhp->fh_export->ex_path.dentry != tfhp->fh_export->ex_path.dentry)
		goto out_dput_new;

	if (nfsd_has_cached_files(ndentry)) {
		has_cached = true;
		goto out_dput_old;
	} else {
		host_err = vfs_rename(fdir, odentry, tdir, ndentry, NULL, 0);
		if (!host_err) {
			host_err = commit_metadata(tfhp);
			if (!host_err)
				host_err = commit_metadata(ffhp);
		}
	}
 out_dput_new:
	dput(ndentry);
 out_dput_old:
	dput(odentry);
 out_nfserr:
	err = nfserrno(host_err);
	/*
	 * We cannot rely on fh_unlock on the two filehandles,
	 * as that would do the wrong thing if the two directories
	 * were the same, so again we do it by hand.
	 */
	if (!has_cached) {
		fill_post_wcc(ffhp);
		fill_post_wcc(tfhp);
	}
	unlock_rename(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = false;
	fh_drop_write(ffhp);

	/*
	 * If the target dentry has cached open files, then we need to try to
	 * close them prior to doing the rename. Flushing delayed fput
	 * shouldn't be done with locks held however, so we delay it until this
	 * point and then reattempt the whole shebang.
	 */
	if (has_cached) {
		has_cached = false;
		nfsd_close_cached_files(ndentry);
		dput(ndentry);
		goto retry;
	}
out:
	return err;
}