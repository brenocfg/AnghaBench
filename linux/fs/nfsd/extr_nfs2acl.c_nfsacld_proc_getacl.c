#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fh_dentry; } ;
typedef  TYPE_1__ svc_fh ;
struct svc_rqst {struct nfsd3_getaclres* rq_resp; struct nfsd3_getaclargs* rq_argp; } ;
struct posix_acl {int dummy; } ;
struct nfsd3_getaclres {int mask; struct posix_acl* acl_default; struct posix_acl* acl_access; int /*<<< orphan*/  stat; int /*<<< orphan*/  fh; } ;
struct nfsd3_getaclargs {int mask; int /*<<< orphan*/  fh; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int NFS_ACL ; 
 int NFS_ACLCNT ; 
 int NFS_ACL_MASK ; 
 int NFS_DFACL ; 
 int NFS_DFACLCNT ; 
 int /*<<< orphan*/  PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  RETURN_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_getattr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct posix_acl* get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

__attribute__((used)) static __be32 nfsacld_proc_getacl(struct svc_rqst *rqstp)
{
	struct nfsd3_getaclargs *argp = rqstp->rq_argp;
	struct nfsd3_getaclres *resp = rqstp->rq_resp;
	struct posix_acl *acl;
	struct inode *inode;
	svc_fh *fh;
	__be32 nfserr = 0;

	dprintk("nfsd: GETACL(2acl)   %s\n", SVCFH_fmt(&argp->fh));

	fh = fh_copy(&resp->fh, &argp->fh);
	nfserr = fh_verify(rqstp, &resp->fh, 0, NFSD_MAY_NOP);
	if (nfserr)
		RETURN_STATUS(nfserr);

	inode = d_inode(fh->fh_dentry);

	if (argp->mask & ~NFS_ACL_MASK)
		RETURN_STATUS(nfserr_inval);
	resp->mask = argp->mask;

	nfserr = fh_getattr(fh, &resp->stat);
	if (nfserr)
		RETURN_STATUS(nfserr);

	if (resp->mask & (NFS_ACL|NFS_ACLCNT)) {
		acl = get_acl(inode, ACL_TYPE_ACCESS);
		if (acl == NULL) {
			/* Solaris returns the inode's minimum ACL. */
			acl = posix_acl_from_mode(inode->i_mode, GFP_KERNEL);
		}
		if (IS_ERR(acl)) {
			nfserr = nfserrno(PTR_ERR(acl));
			goto fail;
		}
		resp->acl_access = acl;
	}
	if (resp->mask & (NFS_DFACL|NFS_DFACLCNT)) {
		/* Check how Solaris handles requests for the Default ACL
		   of a non-directory! */
		acl = get_acl(inode, ACL_TYPE_DEFAULT);
		if (IS_ERR(acl)) {
			nfserr = nfserrno(PTR_ERR(acl));
			goto fail;
		}
		resp->acl_default = acl;
	}

	/* resp->acl_{access,default} are released in nfssvc_release_getacl. */
	RETURN_STATUS(0);

fail:
	posix_acl_release(resp->acl_access);
	posix_acl_release(resp->acl_default);
	RETURN_STATUS(nfserr);
}