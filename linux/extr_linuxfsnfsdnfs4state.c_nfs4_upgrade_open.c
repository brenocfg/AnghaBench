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
struct nfsd4_open {int op_share_deny; int /*<<< orphan*/  op_share_access; } ;
struct nfs4_ol_stateid {unsigned char st_deny_bmap; } ;
struct nfs4_file {int fi_share_deny; int /*<<< orphan*/  fi_lock; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFS4_SHARE_DENY_BOTH ; 
 scalar_t__ nfs4_file_check_deny (struct nfs4_file*,int) ; 
 scalar_t__ nfs4_get_vfs_file (struct svc_rqst*,struct nfs4_file*,struct svc_fh*,struct nfs4_ol_stateid*,struct nfsd4_open*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_truncate (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*) ; 
 int /*<<< orphan*/  reset_union_bmap_deny (unsigned char,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  set_deny (int,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 

__attribute__((used)) static __be32
nfs4_upgrade_open(struct svc_rqst *rqstp, struct nfs4_file *fp, struct svc_fh *cur_fh, struct nfs4_ol_stateid *stp, struct nfsd4_open *open)
{
	__be32 status;
	unsigned char old_deny_bmap = stp->st_deny_bmap;

	if (!test_access(open->op_share_access, stp))
		return nfs4_get_vfs_file(rqstp, fp, cur_fh, stp, open);

	/* test and set deny mode */
	spin_lock(&fp->fi_lock);
	status = nfs4_file_check_deny(fp, open->op_share_deny);
	if (status == nfs_ok) {
		set_deny(open->op_share_deny, stp);
		fp->fi_share_deny |=
				(open->op_share_deny & NFS4_SHARE_DENY_BOTH);
	}
	spin_unlock(&fp->fi_lock);

	if (status != nfs_ok)
		return status;

	status = nfsd4_truncate(rqstp, cur_fh, open);
	if (status != nfs_ok)
		reset_union_bmap_deny(old_deny_bmap, stp);
	return status;
}