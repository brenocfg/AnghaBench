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
struct svc_rqst {struct nfsd3_diropres* rq_resp; struct nfsd3_mknodargs* rq_argp; } ;
struct nfsd3_mknodargs {size_t ftype; scalar_t__ major; scalar_t__ minor; int /*<<< orphan*/  attrs; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
struct nfsd3_diropres {int /*<<< orphan*/  dirfh; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,scalar_t__) ; 
 size_t NF3BAD ; 
 size_t NF3BLK ; 
 size_t NF3CHR ; 
 size_t NF3FIFO ; 
 size_t NF3SOCK ; 
 int /*<<< orphan*/  NFS3_FHSIZE ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_unlock (int /*<<< orphan*/ *) ; 
 int* nfs3_ftypes ; 
 int /*<<< orphan*/  nfsd_create (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
nfsd3_proc_mknod(struct svc_rqst *rqstp)
{
	struct nfsd3_mknodargs *argp = rqstp->rq_argp;
	struct nfsd3_diropres  *resp = rqstp->rq_resp;
	__be32	nfserr;
	int type;
	dev_t	rdev = 0;

	dprintk("nfsd: MKNOD(3)    %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);

	if (argp->ftype == 0 || argp->ftype >= NF3BAD)
		RETURN_STATUS(nfserr_inval);
	if (argp->ftype == NF3CHR || argp->ftype == NF3BLK) {
		rdev = MKDEV(argp->major, argp->minor);
		if (MAJOR(rdev) != argp->major ||
		    MINOR(rdev) != argp->minor)
			RETURN_STATUS(nfserr_inval);
	} else
		if (argp->ftype != NF3SOCK && argp->ftype != NF3FIFO)
			RETURN_STATUS(nfserr_inval);

	type = nfs3_ftypes[argp->ftype];
	nfserr = nfsd_create(rqstp, &resp->dirfh, argp->name, argp->len,
				    &argp->attrs, type, rdev, &resp->fh);
	fh_unlock(&resp->dirfh);
	RETURN_STATUS(nfserr);
}