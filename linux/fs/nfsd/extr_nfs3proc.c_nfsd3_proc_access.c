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
struct svc_rqst {struct nfsd3_accessres* rq_resp; struct nfsd3_accessargs* rq_argp; } ;
struct nfsd3_accessres {int /*<<< orphan*/  access; int /*<<< orphan*/  fh; } ;
struct nfsd3_accessargs {int /*<<< orphan*/  access; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_access (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd3_proc_access(struct svc_rqst *rqstp)
{
	struct nfsd3_accessargs *argp = rqstp->rq_argp;
	struct nfsd3_accessres *resp = rqstp->rq_resp;
	__be32	nfserr;

	dprintk("nfsd: ACCESS(3)   %s 0x%x\n",
				SVCFH_fmt(&argp->fh),
				argp->access);

	fh_copy(&resp->fh, &argp->fh);
	resp->access = argp->access;
	nfserr = nfsd_access(rqstp, &resp->fh, &resp->access, NULL);
	RETURN_STATUS(nfserr);
}