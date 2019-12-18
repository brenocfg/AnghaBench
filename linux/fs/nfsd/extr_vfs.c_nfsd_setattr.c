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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ time_t ;
struct svc_rqst {int dummy; } ;
struct svc_fh {struct dentry* fh_dentry; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct inode {TYPE_1__ i_ctime; int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_CTIME ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_SATTR ; 
 int NFSD_MAY_WRITE ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int commit_metadata (struct svc_fh*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fh_lock (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_unlock (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int) ; 
 int fh_want_write (struct svc_fh*) ; 
 scalar_t__ nfsd_get_write_access (struct svc_rqst*,struct svc_fh*,struct iattr*) ; 
 int /*<<< orphan*/  nfsd_sanitize_attrs (struct inode*,struct iattr*) ; 
 scalar_t__ nfserr_notsync ; 
 scalar_t__ nfserrno (int) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 

__be32
nfsd_setattr(struct svc_rqst *rqstp, struct svc_fh *fhp, struct iattr *iap,
	     int check_guard, time_t guardtime)
{
	struct dentry	*dentry;
	struct inode	*inode;
	int		accmode = NFSD_MAY_SATTR;
	umode_t		ftype = 0;
	__be32		err;
	int		host_err;
	bool		get_write_count;
	bool		size_change = (iap->ia_valid & ATTR_SIZE);

	if (iap->ia_valid & ATTR_SIZE) {
		accmode |= NFSD_MAY_WRITE|NFSD_MAY_OWNER_OVERRIDE;
		ftype = S_IFREG;
	}

	/*
	 * If utimes(2) and friends are called with times not NULL, we should
	 * not set NFSD_MAY_WRITE bit. Otherwise fh_verify->nfsd_permission
	 * will return EACCES, when the caller's effective UID does not match
	 * the owner of the file, and the caller is not privileged. In this
	 * situation, we should return EPERM(notify_change will return this).
	 */
	if (iap->ia_valid & (ATTR_ATIME | ATTR_MTIME)) {
		accmode |= NFSD_MAY_OWNER_OVERRIDE;
		if (!(iap->ia_valid & (ATTR_ATIME_SET | ATTR_MTIME_SET)))
			accmode |= NFSD_MAY_WRITE;
	}

	/* Callers that do fh_verify should do the fh_want_write: */
	get_write_count = !fhp->fh_dentry;

	/* Get inode */
	err = fh_verify(rqstp, fhp, ftype, accmode);
	if (err)
		return err;
	if (get_write_count) {
		host_err = fh_want_write(fhp);
		if (host_err)
			goto out;
	}

	dentry = fhp->fh_dentry;
	inode = d_inode(dentry);

	/* Ignore any mode updates on symlinks */
	if (S_ISLNK(inode->i_mode))
		iap->ia_valid &= ~ATTR_MODE;

	if (!iap->ia_valid)
		return 0;

	nfsd_sanitize_attrs(inode, iap);

	if (check_guard && guardtime != inode->i_ctime.tv_sec)
		return nfserr_notsync;

	/*
	 * The size case is special, it changes the file in addition to the
	 * attributes, and file systems don't expect it to be mixed with
	 * "random" attribute changes.  We thus split out the size change
	 * into a separate call to ->setattr, and do the rest as a separate
	 * setattr call.
	 */
	if (size_change) {
		err = nfsd_get_write_access(rqstp, fhp, iap);
		if (err)
			return err;
	}

	fh_lock(fhp);
	if (size_change) {
		/*
		 * RFC5661, Section 18.30.4:
		 *   Changing the size of a file with SETATTR indirectly
		 *   changes the time_modify and change attributes.
		 *
		 * (and similar for the older RFCs)
		 */
		struct iattr size_attr = {
			.ia_valid	= ATTR_SIZE | ATTR_CTIME | ATTR_MTIME,
			.ia_size	= iap->ia_size,
		};

		host_err = notify_change(dentry, &size_attr, NULL);
		if (host_err)
			goto out_unlock;
		iap->ia_valid &= ~ATTR_SIZE;

		/*
		 * Avoid the additional setattr call below if the only other
		 * attribute that the client sends is the mtime, as we update
		 * it as part of the size change above.
		 */
		if ((iap->ia_valid & ~ATTR_MTIME) == 0)
			goto out_unlock;
	}

	iap->ia_valid |= ATTR_CTIME;
	host_err = notify_change(dentry, iap, NULL);

out_unlock:
	fh_unlock(fhp);
	if (size_change)
		put_write_access(inode);
out:
	if (!host_err)
		host_err = commit_metadata(fhp);
	return nfserrno(host_err);
}