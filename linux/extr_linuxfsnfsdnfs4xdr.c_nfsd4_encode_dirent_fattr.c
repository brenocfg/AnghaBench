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
struct xdr_stream {int dummy; } ;
struct svc_export {int ex_flags; } ;
struct nfsd4_readdir {int /*<<< orphan*/  rd_rqstp; int /*<<< orphan*/  rd_bmval; TYPE_1__* rd_fhp; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  fh_dentry; struct svc_export* fh_export; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int NFSEXP_V4ROOT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  attributes_need_mount (int /*<<< orphan*/ ) ; 
 scalar_t__ check_nfsd_access (struct svc_export*,int /*<<< orphan*/ ) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  exp_get (struct svc_export*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 struct dentry* lookup_one_len_unlocked (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfsd4_encode_fattr (struct xdr_stream*,int /*<<< orphan*/ *,struct svc_export*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfsd_cross_mnt (int /*<<< orphan*/ ,struct dentry**,struct svc_export**) ; 
 scalar_t__ nfsd_mountpoint (struct dentry*,struct svc_export*) ; 
 scalar_t__ nfserr_noent ; 
 scalar_t__ nfserrno (int) ; 

__attribute__((used)) static __be32
nfsd4_encode_dirent_fattr(struct xdr_stream *xdr, struct nfsd4_readdir *cd,
			const char *name, int namlen)
{
	struct svc_export *exp = cd->rd_fhp->fh_export;
	struct dentry *dentry;
	__be32 nfserr;
	int ignore_crossmnt = 0;

	dentry = lookup_one_len_unlocked(name, cd->rd_fhp->fh_dentry, namlen);
	if (IS_ERR(dentry))
		return nfserrno(PTR_ERR(dentry));
	if (d_really_is_negative(dentry)) {
		/*
		 * we're not holding the i_mutex here, so there's
		 * a window where this directory entry could have gone
		 * away.
		 */
		dput(dentry);
		return nfserr_noent;
	}

	exp_get(exp);
	/*
	 * In the case of a mountpoint, the client may be asking for
	 * attributes that are only properties of the underlying filesystem
	 * as opposed to the cross-mounted file system. In such a case,
	 * we will not follow the cross mount and will fill the attribtutes
	 * directly from the mountpoint dentry.
	 */
	if (nfsd_mountpoint(dentry, exp)) {
		int err;

		if (!(exp->ex_flags & NFSEXP_V4ROOT)
				&& !attributes_need_mount(cd->rd_bmval)) {
			ignore_crossmnt = 1;
			goto out_encode;
		}
		/*
		 * Why the heck aren't we just using nfsd_lookup??
		 * Different "."/".." handling?  Something else?
		 * At least, add a comment here to explain....
		 */
		err = nfsd_cross_mnt(cd->rd_rqstp, &dentry, &exp);
		if (err) {
			nfserr = nfserrno(err);
			goto out_put;
		}
		nfserr = check_nfsd_access(exp, cd->rd_rqstp);
		if (nfserr)
			goto out_put;

	}
out_encode:
	nfserr = nfsd4_encode_fattr(xdr, NULL, exp, dentry, cd->rd_bmval,
					cd->rd_rqstp, ignore_crossmnt);
out_put:
	dput(dentry);
	exp_put(exp);
	return nfserr;
}