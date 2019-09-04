#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {struct nfsd3_diropres* rq_resp; struct nfsd3_createargs* rq_argp; } ;
struct nfsd3_diropres {int /*<<< orphan*/  dirfh; int /*<<< orphan*/  fh; } ;
struct TYPE_2__ {int /*<<< orphan*/  ia_valid; } ;
struct nfsd3_createargs {TYPE_1__ attrs; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  NFS3_FHSIZE ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_create (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd3_proc_mkdir(struct svc_rqst *rqstp)
{
	struct nfsd3_createargs *argp = rqstp->rq_argp;
	struct nfsd3_diropres *resp = rqstp->rq_resp;
	__be32	nfserr;

	dprintk("nfsd: MKDIR(3)    %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	argp->attrs.ia_valid &= ~ATTR_SIZE;
	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);
	nfserr = nfsd_create(rqstp, &resp->dirfh, argp->name, argp->len,
				    &argp->attrs, S_IFDIR, 0, &resp->fh);
	fh_unlock(&resp->dirfh);
	RETURN_STATUS(nfserr);
}