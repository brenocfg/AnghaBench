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
struct svc_rqst {struct auth_ops* rq_authop; } ;
struct auth_ops {int (* release ) (struct svc_rqst*) ;} ;

/* Variables and functions */
 int stub1 (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_put_auth_ops (struct auth_ops*) ; 

int svc_authorise(struct svc_rqst *rqstp)
{
	struct auth_ops *aops = rqstp->rq_authop;
	int rv = 0;

	rqstp->rq_authop = NULL;

	if (aops) {
		rv = aops->release(rqstp);
		svc_put_auth_ops(aops);
	}
	return rv;
}