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
struct svc_rqst {struct nfsd_renameargs* rq_argp; } ;
struct nfsd_renameargs {int /*<<< orphan*/  tfh; int /*<<< orphan*/  ffh; int /*<<< orphan*/  tlen; int /*<<< orphan*/  tname; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_rename (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd_proc_rename(struct svc_rqst *rqstp)
{
	struct nfsd_renameargs *argp = rqstp->rq_argp;
	__be32	nfserr;

	dprintk("nfsd: RENAME   %s %.*s -> \n",
		SVCFH_fmt(&argp->ffh), argp->flen, argp->fname);
	dprintk("nfsd:        ->  %s %.*s\n",
		SVCFH_fmt(&argp->tfh), argp->tlen, argp->tname);

	nfserr = nfsd_rename(rqstp, &argp->ffh, argp->fname, argp->flen,
				    &argp->tfh, argp->tname, argp->tlen);
	fh_put(&argp->ffh);
	fh_put(&argp->tfh);
	return nfserr;
}