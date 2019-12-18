#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fh_dentry; } ;
typedef  TYPE_1__ svc_fh ;
struct svc_rqst {struct nfsd_attrstat* rq_resp; struct nfsd3_setaclargs* rq_argp; } ;
struct nfsd_attrstat {int /*<<< orphan*/  stat; int /*<<< orphan*/  fh; } ;
struct nfsd3_setaclargs {int /*<<< orphan*/  acl_default; int /*<<< orphan*/  acl_access; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  NFSD_MAY_SATTR ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_drop_write (TYPE_1__*) ; 
 scalar_t__ fh_getattr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  fh_unlock (TYPE_1__*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fh_want_write (TYPE_1__*) ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  posix_acl_release (int /*<<< orphan*/ ) ; 
 int set_posix_acl (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfsacld_proc_setacl(struct svc_rqst *rqstp)
{
	struct nfsd3_setaclargs *argp = rqstp->rq_argp;
	struct nfsd_attrstat *resp = rqstp->rq_resp;
	struct inode *inode;
	svc_fh *fh;
	__be32 nfserr = 0;
	int error;

	dprintk("nfsd: SETACL(2acl)   %s\n", SVCFH_fmt(&argp->fh));

	fh = fh_copy(&resp->fh, &argp->fh);
	nfserr = fh_verify(rqstp, &resp->fh, 0, NFSD_MAY_SATTR);
	if (nfserr)
		goto out;

	inode = d_inode(fh->fh_dentry);

	error = fh_want_write(fh);
	if (error)
		goto out_errno;

	fh_lock(fh);

	error = set_posix_acl(inode, ACL_TYPE_ACCESS, argp->acl_access);
	if (error)
		goto out_drop_lock;
	error = set_posix_acl(inode, ACL_TYPE_DEFAULT, argp->acl_default);
	if (error)
		goto out_drop_lock;

	fh_unlock(fh);

	fh_drop_write(fh);

	nfserr = fh_getattr(fh, &resp->stat);

out:
	/* argp->acl_{access,default} may have been allocated in
	   nfssvc_decode_setaclargs. */
	posix_acl_release(argp->acl_access);
	posix_acl_release(argp->acl_default);
	return nfserr;
out_drop_lock:
	fh_unlock(fh);
	fh_drop_write(fh);
out_errno:
	nfserr = nfserrno(error);
	goto out;
}