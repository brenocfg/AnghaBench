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
struct nfsd_attrstat {int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsaclsvc_release_attrstat(struct svc_rqst *rqstp)
{
	struct nfsd_attrstat *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
}