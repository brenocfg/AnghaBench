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
struct svc_rqst {struct nfsd_readlinkres* rq_resp; struct nfsd_readlinkargs* rq_argp; } ;
struct nfsd_readlinkres {int /*<<< orphan*/  len; } ;
struct nfsd_readlinkargs {int /*<<< orphan*/  fh; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_MAXPATHLEN ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_readlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd_proc_readlink(struct svc_rqst *rqstp)
{
	struct nfsd_readlinkargs *argp = rqstp->rq_argp;
	struct nfsd_readlinkres *resp = rqstp->rq_resp;
	__be32	nfserr;

	dprintk("nfsd: READLINK %s\n", SVCFH_fmt(&argp->fh));

	/* Read the symlink. */
	resp->len = NFS_MAXPATHLEN;
	nfserr = nfsd_readlink(rqstp, &argp->fh, argp->buffer, &resp->len);

	fh_put(&argp->fh);
	return nfserr;
}