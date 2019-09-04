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
struct svc_rqst {struct nfsd_diropargs* rq_argp; } ;
struct nfsd_diropargs {int /*<<< orphan*/  fh; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_unlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd_proc_remove(struct svc_rqst *rqstp)
{
	struct nfsd_diropargs *argp = rqstp->rq_argp;
	__be32	nfserr;

	dprintk("nfsd: REMOVE   %s %.*s\n", SVCFH_fmt(&argp->fh),
		argp->len, argp->name);

	/* Unlink. -SIFDIR means file must not be a directory */
	nfserr = nfsd_unlink(rqstp, &argp->fh, -S_IFDIR, argp->name, argp->len);
	fh_put(&argp->fh);
	return nfserr;
}