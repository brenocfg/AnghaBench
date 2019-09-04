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
struct svc_fh {int dummy; } ;
struct svc_export {int dummy; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_EXEC ; 
 int /*<<< orphan*/  S_IFDIR ; 
 scalar_t__ check_nfsd_access (struct svc_export*,struct svc_rqst*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 scalar_t__ fh_compose (struct svc_fh*,struct svc_export*,struct dentry*,struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd_lookup_dentry (struct svc_rqst*,struct svc_fh*,char const*,unsigned int,struct svc_export**,struct dentry**) ; 
 scalar_t__ nfserr_noent ; 

__be32
nfsd_lookup(struct svc_rqst *rqstp, struct svc_fh *fhp, const char *name,
				unsigned int len, struct svc_fh *resfh)
{
	struct svc_export	*exp;
	struct dentry		*dentry;
	__be32 err;

	err = fh_verify(rqstp, fhp, S_IFDIR, NFSD_MAY_EXEC);
	if (err)
		return err;
	err = nfsd_lookup_dentry(rqstp, fhp, name, len, &exp, &dentry);
	if (err)
		return err;
	err = check_nfsd_access(exp, rqstp);
	if (err)
		goto out;
	/*
	 * Note: we compose the file handle now, but as the
	 * dentry may be negative, it may need to be updated.
	 */
	err = fh_compose(resfh, exp, dentry, fhp);
	if (!err && d_really_is_negative(dentry))
		err = nfserr_noent;
out:
	dput(dentry);
	exp_put(exp);
	return err;
}