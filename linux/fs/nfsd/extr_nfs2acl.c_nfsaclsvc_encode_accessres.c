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
struct svc_rqst {struct nfsd3_accessres* rq_resp; } ;
struct nfsd3_accessres {int /*<<< orphan*/  access; int /*<<< orphan*/  stat; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs2svc_encode_fattr (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsaclsvc_encode_accessres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_accessres *resp = rqstp->rq_resp;

	p = nfs2svc_encode_fattr(rqstp, p, &resp->fh, &resp->stat);
	*p++ = htonl(resp->access);
	return xdr_ressize_check(rqstp, p);
}