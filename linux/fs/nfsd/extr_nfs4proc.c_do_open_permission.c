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
struct nfsd4_open {int op_share_access; int op_share_deny; scalar_t__ op_truncate; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_SHARE_ACCESS_READ ; 
 int NFS4_SHARE_ACCESS_WRITE ; 
 int NFS4_SHARE_DENY_READ ; 
 int NFSD_MAY_READ ; 
 int NFSD_MAY_READ_IF_EXEC ; 
 int NFSD_MAY_TRUNC ; 
 int NFSD_MAY_WRITE ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
do_open_permission(struct svc_rqst *rqstp, struct svc_fh *current_fh, struct nfsd4_open *open, int accmode)
{
	__be32 status;

	if (open->op_truncate &&
		!(open->op_share_access & NFS4_SHARE_ACCESS_WRITE))
		return nfserr_inval;

	accmode |= NFSD_MAY_READ_IF_EXEC;

	if (open->op_share_access & NFS4_SHARE_ACCESS_READ)
		accmode |= NFSD_MAY_READ;
	if (open->op_share_access & NFS4_SHARE_ACCESS_WRITE)
		accmode |= (NFSD_MAY_WRITE | NFSD_MAY_TRUNC);
	if (open->op_share_deny & NFS4_SHARE_DENY_READ)
		accmode |= NFSD_MAY_WRITE;

	status = fh_verify(rqstp, current_fh, S_IFREG, accmode);

	return status;
}