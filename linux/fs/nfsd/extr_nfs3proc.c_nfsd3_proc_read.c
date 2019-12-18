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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_vec; struct nfsd3_readres* rq_resp; struct nfsd3_readargs* rq_argp; } ;
struct nfsd3_readres {unsigned long count; int /*<<< orphan*/  eof; int /*<<< orphan*/  fh; } ;
struct nfsd3_readargs {int /*<<< orphan*/  vlen; scalar_t__ offset; int /*<<< orphan*/  fh; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS3_POST_OP_ATTR_WORDS ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_read (struct svc_rqst*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_max_payload (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_reserve_auth (struct svc_rqst*,int) ; 

__attribute__((used)) static __be32
nfsd3_proc_read(struct svc_rqst *rqstp)
{
	struct nfsd3_readargs *argp = rqstp->rq_argp;
	struct nfsd3_readres *resp = rqstp->rq_resp;
	__be32	nfserr;
	u32	max_blocksize = svc_max_payload(rqstp);
	unsigned long cnt = min(argp->count, max_blocksize);

	dprintk("nfsd: READ(3) %s %lu bytes at %Lu\n",
				SVCFH_fmt(&argp->fh),
				(unsigned long) argp->count,
				(unsigned long long) argp->offset);

	/* Obtain buffer pointer for payload.
	 * 1 (status) + 22 (post_op_attr) + 1 (count) + 1 (eof)
	 * + 1 (xdr opaque byte count) = 26
	 */
	resp->count = cnt;
	svc_reserve_auth(rqstp, ((1 + NFS3_POST_OP_ATTR_WORDS + 3)<<2) + resp->count +4);

	fh_copy(&resp->fh, &argp->fh);
	nfserr = nfsd_read(rqstp, &resp->fh,
				  argp->offset,
			   	  rqstp->rq_vec, argp->vlen,
				  &resp->count,
				  &resp->eof);
	RETURN_STATUS(nfserr);
}