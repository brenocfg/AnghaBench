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
struct svc_rqst {struct nfsd3_commitres* rq_resp; } ;
struct nfsd_net {int dummy; } ;
struct nfsd3_commitres {scalar_t__ status; int /*<<< orphan*/  fh; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 void** encode_wcc_data (struct svc_rqst*,void**,int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_copy_boot_verifier (void**,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int xdr_ressize_check (struct svc_rqst*,void**) ; 

int
nfs3svc_encode_commitres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_commitres *resp = rqstp->rq_resp;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	__be32 verf[2];

	p = encode_wcc_data(rqstp, p, &resp->fh);
	/* Write verifier */
	if (resp->status == 0) {
		/* unique identifier, y2038 overflow can be ignored */
		nfsd_copy_boot_verifier(verf, nn);
		*p++ = verf[0];
		*p++ = verf[1];
	}
	return xdr_ressize_check(rqstp, p);
}