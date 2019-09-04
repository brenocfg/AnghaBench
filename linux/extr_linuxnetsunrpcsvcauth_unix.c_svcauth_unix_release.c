#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * cr_group_info; } ;
struct svc_rqst {TYPE_1__ rq_cred; int /*<<< orphan*/ * rq_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_domain_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_group_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
svcauth_unix_release(struct svc_rqst *rqstp)
{
	/* Verifier (such as it is) is already in place.
	 */
	if (rqstp->rq_client)
		auth_domain_put(rqstp->rq_client);
	rqstp->rq_client = NULL;
	if (rqstp->rq_cred.cr_group_info)
		put_group_info(rqstp->rq_cred.cr_group_info);
	rqstp->rq_cred.cr_group_info = NULL;

	return 0;
}