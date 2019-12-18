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
struct svc_rqst {struct nfsd3_diropres* rq_resp; struct nfsd3_diropargs* rq_argp; } ;
struct nfsd3_diropres {int /*<<< orphan*/  fh; int /*<<< orphan*/  dirfh; } ;
struct nfsd3_diropargs {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS3_FHSIZE ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_lookup (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd3_proc_lookup(struct svc_rqst *rqstp)
{
	struct nfsd3_diropargs *argp = rqstp->rq_argp;
	struct nfsd3_diropres  *resp = rqstp->rq_resp;
	__be32	nfserr;

	dprintk("nfsd: LOOKUP(3)   %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);

	nfserr = nfsd_lookup(rqstp, &resp->dirfh,
				    argp->name,
				    argp->len,
				    &resp->fh);
	RETURN_STATUS(nfserr);
}