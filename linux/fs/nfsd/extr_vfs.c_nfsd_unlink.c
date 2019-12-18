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
struct svc_rqst {int dummy; } ;
struct svc_fh {struct dentry* fh_dentry; } ;
struct inode {int i_mode; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  NFSD_MAY_REMOVE ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int commit_metadata (struct svc_fh*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_lock_nested (struct svc_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int,int /*<<< orphan*/ ) ; 
 int fh_want_write (struct svc_fh*) ; 
 scalar_t__ isdotent (char*,int) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int /*<<< orphan*/  nfsd_close_cached_files (struct dentry*) ; 
 scalar_t__ nfserr_acces ; 
 scalar_t__ nfserrno (int) ; 
 int vfs_rmdir (struct inode*,struct dentry*) ; 
 int vfs_unlink (struct inode*,struct dentry*,int /*<<< orphan*/ *) ; 

__be32
nfsd_unlink(struct svc_rqst *rqstp, struct svc_fh *fhp, int type,
				char *fname, int flen)
{
	struct dentry	*dentry, *rdentry;
	struct inode	*dirp;
	__be32		err;
	int		host_err;

	err = nfserr_acces;
	if (!flen || isdotent(fname, flen))
		goto out;
	err = fh_verify(rqstp, fhp, S_IFDIR, NFSD_MAY_REMOVE);
	if (err)
		goto out;

	host_err = fh_want_write(fhp);
	if (host_err)
		goto out_nfserr;

	fh_lock_nested(fhp, I_MUTEX_PARENT);
	dentry = fhp->fh_dentry;
	dirp = d_inode(dentry);

	rdentry = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(rdentry);
	if (IS_ERR(rdentry))
		goto out_drop_write;

	if (d_really_is_negative(rdentry)) {
		dput(rdentry);
		host_err = -ENOENT;
		goto out_drop_write;
	}

	if (!type)
		type = d_inode(rdentry)->i_mode & S_IFMT;

	if (type != S_IFDIR) {
		nfsd_close_cached_files(rdentry);
		host_err = vfs_unlink(dirp, rdentry, NULL);
	} else {
		host_err = vfs_rmdir(dirp, rdentry);
	}

	if (!host_err)
		host_err = commit_metadata(fhp);
	dput(rdentry);

out_drop_write:
	fh_drop_write(fhp);
out_nfserr:
	err = nfserrno(host_err);
out:
	return err;
}