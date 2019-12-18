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
struct nfsd_file {int dummy; } ;
struct nfsd4_open {int op_share_deny; int /*<<< orphan*/  op_share_access; } ;
struct nfs4_ol_stateid {unsigned char st_access_bmap; unsigned char st_deny_bmap; } ;
struct nfs4_file {int fi_share_deny; int /*<<< orphan*/  fi_lock; struct nfsd_file** fi_fds; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFS4_SHARE_DENY_BOTH ; 
 int /*<<< orphan*/  bmap_to_share_mode (unsigned char) ; 
 int nfs4_access_to_access (int /*<<< orphan*/ ) ; 
 int nfs4_access_to_omode (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_file_check_deny (struct nfs4_file*,int) ; 
 scalar_t__ nfs4_file_get_access (struct nfs4_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_file_put_access (struct nfs4_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_truncate (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*) ; 
 scalar_t__ nfsd_file_acquire (struct svc_rqst*,struct svc_fh*,int,struct nfsd_file**) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 int /*<<< orphan*/  reset_union_bmap_deny (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  set_access (int /*<<< orphan*/ ,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  set_deny (int,struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 nfs4_get_vfs_file(struct svc_rqst *rqstp, struct nfs4_file *fp,
		struct svc_fh *cur_fh, struct nfs4_ol_stateid *stp,
		struct nfsd4_open *open)
{
	struct nfsd_file *nf = NULL;
	__be32 status;
	int oflag = nfs4_access_to_omode(open->op_share_access);
	int access = nfs4_access_to_access(open->op_share_access);
	unsigned char old_access_bmap, old_deny_bmap;

	spin_lock(&fp->fi_lock);

	/*
	 * Are we trying to set a deny mode that would conflict with
	 * current access?
	 */
	status = nfs4_file_check_deny(fp, open->op_share_deny);
	if (status != nfs_ok) {
		spin_unlock(&fp->fi_lock);
		goto out;
	}

	/* set access to the file */
	status = nfs4_file_get_access(fp, open->op_share_access);
	if (status != nfs_ok) {
		spin_unlock(&fp->fi_lock);
		goto out;
	}

	/* Set access bits in stateid */
	old_access_bmap = stp->st_access_bmap;
	set_access(open->op_share_access, stp);

	/* Set new deny mask */
	old_deny_bmap = stp->st_deny_bmap;
	set_deny(open->op_share_deny, stp);
	fp->fi_share_deny |= (open->op_share_deny & NFS4_SHARE_DENY_BOTH);

	if (!fp->fi_fds[oflag]) {
		spin_unlock(&fp->fi_lock);
		status = nfsd_file_acquire(rqstp, cur_fh, access, &nf);
		if (status)
			goto out_put_access;
		spin_lock(&fp->fi_lock);
		if (!fp->fi_fds[oflag]) {
			fp->fi_fds[oflag] = nf;
			nf = NULL;
		}
	}
	spin_unlock(&fp->fi_lock);
	if (nf)
		nfsd_file_put(nf);

	status = nfsd4_truncate(rqstp, cur_fh, open);
	if (status)
		goto out_put_access;
out:
	return status;
out_put_access:
	stp->st_access_bmap = old_access_bmap;
	nfs4_file_put_access(fp, open->op_share_access);
	reset_union_bmap_deny(bmap_to_share_mode(old_deny_bmap), stp);
	goto out;
}