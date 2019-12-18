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
struct svc_rqst {struct nlm_res* rq_resp; } ;
struct nlm_res {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * nlm4_encode_testres (int /*<<< orphan*/ *,struct nlm_res*) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nlm4svc_encode_testres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nlm_res *resp = rqstp->rq_resp;

	if (!(p = nlm4_encode_testres(p, resp)))
		return 0;
	return xdr_ressize_check(rqstp, p);
}