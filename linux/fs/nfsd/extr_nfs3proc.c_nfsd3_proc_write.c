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
struct TYPE_2__ {int /*<<< orphan*/  pages; } ;
struct svc_rqst {int /*<<< orphan*/  rq_vec; TYPE_1__ rq_arg; struct nfsd3_writeres* rq_resp; struct nfsd3_writeargs* rq_argp; } ;
struct nfsd3_writeres {unsigned long count; scalar_t__ committed; int /*<<< orphan*/  fh; } ;
struct nfsd3_writeargs {unsigned long len; scalar_t__ offset; int /*<<< orphan*/  first; scalar_t__ stable; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long long,char*) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_write (struct svc_rqst*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,unsigned int,unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  nfserr_io ; 
 unsigned int svc_fill_write_vector (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __be32
nfsd3_proc_write(struct svc_rqst *rqstp)
{
	struct nfsd3_writeargs *argp = rqstp->rq_argp;
	struct nfsd3_writeres *resp = rqstp->rq_resp;
	__be32	nfserr;
	unsigned long cnt = argp->len;
	unsigned int nvecs;

	dprintk("nfsd: WRITE(3)    %s %d bytes at %Lu%s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				(unsigned long long) argp->offset,
				argp->stable? " stable" : "");

	fh_copy(&resp->fh, &argp->fh);
	resp->committed = argp->stable;
	nvecs = svc_fill_write_vector(rqstp, rqstp->rq_arg.pages,
				      &argp->first, cnt);
	if (!nvecs)
		RETURN_STATUS(nfserr_io);
	nfserr = nfsd_write(rqstp, &resp->fh, argp->offset,
			    rqstp->rq_vec, nvecs, &cnt,
			    resp->committed);
	resp->count = cnt;
	RETURN_STATUS(nfserr);
}