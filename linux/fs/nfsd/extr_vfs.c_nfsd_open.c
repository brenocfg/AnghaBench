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
typedef  scalar_t__ umode_t ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFSD_MAY_OWNER_OVERRIDE ; 
 scalar_t__ S_IFREG ; 
 scalar_t__ __nfsd_open (struct svc_rqst*,struct svc_fh*,scalar_t__,int,struct file**) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,scalar_t__,int) ; 
 int /*<<< orphan*/  validate_process_creds () ; 

__be32
nfsd_open(struct svc_rqst *rqstp, struct svc_fh *fhp, umode_t type,
		int may_flags, struct file **filp)
{
	__be32 err;

	validate_process_creds();
	/*
	 * If we get here, then the client has already done an "open",
	 * and (hopefully) checked permission - so allow OWNER_OVERRIDE
	 * in case a chmod has now revoked permission.
	 *
	 * Arguably we should also allow the owner override for
	 * directories, but we never have and it doesn't seem to have
	 * caused anyone a problem.  If we were to change this, note
	 * also that our filldir callbacks would need a variant of
	 * lookup_one_len that doesn't check permissions.
	 */
	if (type == S_IFREG)
		may_flags |= NFSD_MAY_OWNER_OVERRIDE;
	err = fh_verify(rqstp, fhp, type, may_flags);
	if (!err)
		err = __nfsd_open(rqstp, fhp, type, may_flags, filp);
	validate_process_creds();
	return err;
}