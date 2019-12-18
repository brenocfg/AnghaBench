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
struct svc_fh {int /*<<< orphan*/  fh_dentry; int /*<<< orphan*/  fh_export; } ;
struct nfsd_file {int dummy; } ;
struct nfs4_stid {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_READ ; 
 int NFSD_MAY_WRITE ; 
 int RD_STATE ; 
 struct nfsd_file* nfs4_find_file (struct nfs4_stid*,int) ; 
 scalar_t__ nfsd_file_acquire (struct svc_rqst*,struct svc_fh*,int,struct nfsd_file**) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 scalar_t__ nfsd_permission (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __be32
nfs4_check_file(struct svc_rqst *rqstp, struct svc_fh *fhp, struct nfs4_stid *s,
		struct nfsd_file **nfp, int flags)
{
	int acc = (flags & RD_STATE) ? NFSD_MAY_READ : NFSD_MAY_WRITE;
	struct nfsd_file *nf;
	__be32 status;

	nf = nfs4_find_file(s, flags);
	if (nf) {
		status = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				acc | NFSD_MAY_OWNER_OVERRIDE);
		if (status) {
			nfsd_file_put(nf);
			goto out;
		}
	} else {
		status = nfsd_file_acquire(rqstp, fhp, acc, &nf);
		if (status)
			return status;
	}
	*nfp = nf;
out:
	return status;
}