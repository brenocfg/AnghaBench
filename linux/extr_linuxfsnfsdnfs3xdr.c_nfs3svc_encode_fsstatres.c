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
typedef  int u64 ;
struct svc_rqst {struct nfsd3_fsstatres* rq_resp; } ;
struct kstatfs {int f_bsize; int f_blocks; int f_bfree; int f_bavail; int f_files; int f_ffree; } ;
struct nfsd3_fsstatres {scalar_t__ status; int /*<<< orphan*/  invarsec; struct kstatfs stats; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_zero ; 

int
nfs3svc_encode_fsstatres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_fsstatres *resp = rqstp->rq_resp;
	struct kstatfs	*s = &resp->stats;
	u64		bs = s->f_bsize;

	*p++ = xdr_zero;	/* no post_op_attr */

	if (resp->status == 0) {
		p = xdr_encode_hyper(p, bs * s->f_blocks);	/* total bytes */
		p = xdr_encode_hyper(p, bs * s->f_bfree);	/* free bytes */
		p = xdr_encode_hyper(p, bs * s->f_bavail);	/* user available bytes */
		p = xdr_encode_hyper(p, s->f_files);	/* total inodes */
		p = xdr_encode_hyper(p, s->f_ffree);	/* free inodes */
		p = xdr_encode_hyper(p, s->f_ffree);	/* user available inodes */
		*p++ = htonl(resp->invarsec);	/* mean unchanged time */
	}
	return xdr_ressize_check(rqstp, p);
}