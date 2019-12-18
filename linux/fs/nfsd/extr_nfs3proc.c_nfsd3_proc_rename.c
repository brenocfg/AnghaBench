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
struct svc_rqst {struct nfsd3_renameres* rq_resp; struct nfsd3_renameargs* rq_argp; } ;
struct nfsd3_renameres {int /*<<< orphan*/  tfh; int /*<<< orphan*/  ffh; } ;
struct nfsd3_renameargs {int /*<<< orphan*/  tlen; int /*<<< orphan*/  tname; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; int /*<<< orphan*/  tfh; int /*<<< orphan*/  ffh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_rename (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd3_proc_rename(struct svc_rqst *rqstp)
{
	struct nfsd3_renameargs *argp = rqstp->rq_argp;
	struct nfsd3_renameres *resp = rqstp->rq_resp;
	__be32	nfserr;

	dprintk("nfsd: RENAME(3)   %s %.*s ->\n",
				SVCFH_fmt(&argp->ffh),
				argp->flen,
				argp->fname);
	dprintk("nfsd: -> %s %.*s\n",
				SVCFH_fmt(&argp->tfh),
				argp->tlen,
				argp->tname);

	fh_copy(&resp->ffh, &argp->ffh);
	fh_copy(&resp->tfh, &argp->tfh);
	nfserr = nfsd_rename(rqstp, &resp->ffh, argp->fname, argp->flen,
				    &resp->tfh, argp->tname, argp->tlen);
	RETURN_STATUS(nfserr);
}