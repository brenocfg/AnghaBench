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
struct svc_rqst {struct nfsd_attrstat* rq_resp; } ;
struct nfsd_attrstat {int /*<<< orphan*/  stat; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * nfs2svc_encode_fattr (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsaclsvc_encode_attrstatres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd_attrstat *resp = rqstp->rq_resp;

	p = nfs2svc_encode_fattr(rqstp, p, &resp->fh, &resp->stat);
	return xdr_ressize_check(rqstp, p);
}