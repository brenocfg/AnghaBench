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
struct svc_rqst {int /*<<< orphan*/  rq_vec; TYPE_1__ rq_arg; struct nfsd_attrstat* rq_resp; struct nfsd_writeargs* rq_argp; } ;
struct nfsd_writeargs {unsigned long len; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; int /*<<< orphan*/  first; } ;
struct nfsd_attrstat {int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DATA_SYNC ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_return_attrs (int /*<<< orphan*/ ,struct nfsd_attrstat*) ; 
 int /*<<< orphan*/  nfsd_write (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_io ; 
 unsigned int svc_fill_write_vector (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __be32
nfsd_proc_write(struct svc_rqst *rqstp)
{
	struct nfsd_writeargs *argp = rqstp->rq_argp;
	struct nfsd_attrstat *resp = rqstp->rq_resp;
	__be32	nfserr;
	unsigned long cnt = argp->len;
	unsigned int nvecs;

	dprintk("nfsd: WRITE    %s %d bytes at %d\n",
		SVCFH_fmt(&argp->fh),
		argp->len, argp->offset);

	nvecs = svc_fill_write_vector(rqstp, rqstp->rq_arg.pages,
				      &argp->first, cnt);
	if (!nvecs)
		return nfserr_io;
	nfserr = nfsd_write(rqstp, fh_copy(&resp->fh, &argp->fh),
			    argp->offset, rqstp->rq_vec, nvecs,
			    &cnt, NFS_DATA_SYNC);
	return nfsd_return_attrs(nfserr, resp);
}