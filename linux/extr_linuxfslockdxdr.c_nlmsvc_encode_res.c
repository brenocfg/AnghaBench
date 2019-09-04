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
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * nlm_encode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nlmsvc_encode_res(struct svc_rqst *rqstp, __be32 *p)
{
	struct nlm_res *resp = rqstp->rq_resp;

	if (!(p = nlm_encode_cookie(p, &resp->cookie)))
		return 0;
	*p++ = resp->status;
	return xdr_ressize_check(rqstp, p);
}