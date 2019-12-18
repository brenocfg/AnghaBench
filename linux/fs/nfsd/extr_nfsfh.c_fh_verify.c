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
typedef  int /*<<< orphan*/  umode_t ;
struct svc_rqst {int dummy; } ;
struct svc_fh {struct svc_export* fh_export; struct dentry* fh_dentry; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct svc_export {TYPE_1__ ex_path; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  fh_stale; } ;

/* Variables and functions */
 int NFSD_MAY_BYPASS_GSS ; 
 int NFSD_MAY_BYPASS_GSS_ON_ROOT ; 
 int NFSD_MAY_LOCK ; 
 int /*<<< orphan*/  SVCFH_fmt (struct svc_fh*) ; 
 scalar_t__ check_nfsd_access (struct svc_export*,struct svc_rqst*) ; 
 scalar_t__ check_pseudo_root (struct svc_rqst*,struct dentry*,struct svc_export*) ; 
 int /*<<< orphan*/  dprintk (char*,struct dentry*,...) ; 
 scalar_t__ nfsd_mode_check (struct svc_rqst*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd_permission (struct svc_rqst*,struct svc_export*,struct dentry*,int) ; 
 scalar_t__ nfsd_set_fh_dentry (struct svc_rqst*,struct svc_fh*) ; 
 scalar_t__ nfsd_setuser_and_check_port (struct svc_rqst*,struct svc_export*) ; 
 TYPE_2__ nfsdstats ; 
 scalar_t__ nfserr_stale ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 

__be32
fh_verify(struct svc_rqst *rqstp, struct svc_fh *fhp, umode_t type, int access)
{
	struct svc_export *exp;
	struct dentry	*dentry;
	__be32		error;

	dprintk("nfsd: fh_verify(%s)\n", SVCFH_fmt(fhp));

	if (!fhp->fh_dentry) {
		error = nfsd_set_fh_dentry(rqstp, fhp);
		if (error)
			goto out;
	}
	dentry = fhp->fh_dentry;
	exp = fhp->fh_export;
	/*
	 * We still have to do all these permission checks, even when
	 * fh_dentry is already set:
	 * 	- fh_verify may be called multiple times with different
	 * 	  "access" arguments (e.g. nfsd_proc_create calls
	 * 	  fh_verify(...,NFSD_MAY_EXEC) first, then later (in
	 * 	  nfsd_create) calls fh_verify(...,NFSD_MAY_CREATE).
	 *	- in the NFSv4 case, the filehandle may have been filled
	 *	  in by fh_compose, and given a dentry, but further
	 *	  compound operations performed with that filehandle
	 *	  still need permissions checks.  In the worst case, a
	 *	  mountpoint crossing may have changed the export
	 *	  options, and we may now need to use a different uid
	 *	  (for example, if different id-squashing options are in
	 *	  effect on the new filesystem).
	 */
	error = check_pseudo_root(rqstp, dentry, exp);
	if (error)
		goto out;

	error = nfsd_setuser_and_check_port(rqstp, exp);
	if (error)
		goto out;

	error = nfsd_mode_check(rqstp, dentry, type);
	if (error)
		goto out;

	/*
	 * pseudoflavor restrictions are not enforced on NLM,
	 * which clients virtually always use auth_sys for,
	 * even while using RPCSEC_GSS for NFS.
	 */
	if (access & NFSD_MAY_LOCK || access & NFSD_MAY_BYPASS_GSS)
		goto skip_pseudoflavor_check;
	/*
	 * Clients may expect to be able to use auth_sys during mount,
	 * even if they use gss for everything else; see section 2.3.2
	 * of rfc 2623.
	 */
	if (access & NFSD_MAY_BYPASS_GSS_ON_ROOT
			&& exp->ex_path.dentry == dentry)
		goto skip_pseudoflavor_check;

	error = check_nfsd_access(exp, rqstp);
	if (error)
		goto out;

skip_pseudoflavor_check:
	/* Finally, check access permissions. */
	error = nfsd_permission(rqstp, exp, dentry, access);

	if (error) {
		dprintk("fh_verify: %pd2 permission failure, "
			"acc=%x, error=%d\n",
			dentry,
			access, ntohl(error));
	}
out:
	if (error == nfserr_stale)
		nfsdstats.fh_stale++;
	return error;
}