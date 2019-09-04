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
struct nfs4_stid {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_READ ; 
 int NFSD_MAY_WRITE ; 
 int RD_STATE ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* nfs4_find_file (struct nfs4_stid*,int) ; 
 scalar_t__ nfsd_open (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int,struct file**) ; 
 scalar_t__ nfsd_permission (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __be32
nfs4_check_file(struct svc_rqst *rqstp, struct svc_fh *fhp, struct nfs4_stid *s,
		struct file **filpp, bool *tmp_file, int flags)
{
	int acc = (flags & RD_STATE) ? NFSD_MAY_READ : NFSD_MAY_WRITE;
	struct file *file;
	__be32 status;

	file = nfs4_find_file(s, flags);
	if (file) {
		status = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				acc | NFSD_MAY_OWNER_OVERRIDE);
		if (status) {
			fput(file);
			return status;
		}

		*filpp = file;
	} else {
		status = nfsd_open(rqstp, fhp, S_IFREG, acc, filpp);
		if (status)
			return status;

		if (tmp_file)
			*tmp_file = true;
	}

	return 0;
}