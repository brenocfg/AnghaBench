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
struct svc_rqst {struct nfsd3_fsinfores* rq_resp; } ;
struct nfsd3_fsinfores {scalar_t__ status; int /*<<< orphan*/  f_properties; int /*<<< orphan*/  f_maxfilesize; int /*<<< orphan*/  f_dtpref; int /*<<< orphan*/  f_wtmult; int /*<<< orphan*/  f_wtpref; int /*<<< orphan*/  f_wtmax; int /*<<< orphan*/  f_rtmult; int /*<<< orphan*/  f_rtpref; int /*<<< orphan*/  f_rtmax; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_one ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 void* xdr_zero ; 

int
nfs3svc_encode_fsinfores(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_fsinfores *resp = rqstp->rq_resp;

	*p++ = xdr_zero;	/* no post_op_attr */

	if (resp->status == 0) {
		*p++ = htonl(resp->f_rtmax);
		*p++ = htonl(resp->f_rtpref);
		*p++ = htonl(resp->f_rtmult);
		*p++ = htonl(resp->f_wtmax);
		*p++ = htonl(resp->f_wtpref);
		*p++ = htonl(resp->f_wtmult);
		*p++ = htonl(resp->f_dtpref);
		p = xdr_encode_hyper(p, resp->f_maxfilesize);
		*p++ = xdr_one;
		*p++ = xdr_zero;
		*p++ = htonl(resp->f_properties);
	}

	return xdr_ressize_check(rqstp, p);
}