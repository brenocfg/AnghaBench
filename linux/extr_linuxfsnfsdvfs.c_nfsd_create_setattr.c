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
typedef  int /*<<< orphan*/  time_t ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct iattr {int ia_valid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  commit_metadata (struct svc_fh*) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  nfsd_setattr (struct svc_rqst*,struct svc_fh*,struct iattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd_create_setattr(struct svc_rqst *rqstp, struct svc_fh *resfhp,
			struct iattr *iap)
{
	/*
	 * Mode has already been set earlier in create:
	 */
	iap->ia_valid &= ~ATTR_MODE;
	/*
	 * Setting uid/gid works only for root.  Irix appears to
	 * send along the gid on create when it tries to implement
	 * setgid directories via NFS:
	 */
	if (!uid_eq(current_fsuid(), GLOBAL_ROOT_UID))
		iap->ia_valid &= ~(ATTR_UID|ATTR_GID);
	if (iap->ia_valid)
		return nfsd_setattr(rqstp, resfhp, iap, 0, (time_t)0);
	/* Callers expect file metadata to be committed here */
	return nfserrno(commit_metadata(resfhp));
}