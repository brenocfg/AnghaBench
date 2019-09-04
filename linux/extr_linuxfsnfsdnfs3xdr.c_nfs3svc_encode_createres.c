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
struct svc_rqst {struct nfsd3_diropres* rq_resp; } ;
struct nfsd3_diropres {scalar_t__ status; int /*<<< orphan*/  dirfh; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * encode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_post_op_attr (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_wcc_data (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_one ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfs3svc_encode_createres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_diropres *resp = rqstp->rq_resp;

	if (resp->status == 0) {
		*p++ = xdr_one;
		p = encode_fh(p, &resp->fh);
		p = encode_post_op_attr(rqstp, p, &resp->fh);
	}
	p = encode_wcc_data(rqstp, p, &resp->dirfh);
	return xdr_ressize_check(rqstp, p);
}