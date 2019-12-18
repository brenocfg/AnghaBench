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
struct TYPE_2__ {int /*<<< orphan*/ * head; } ;
struct svc_rqst {struct auth_ops* rq_authop; int /*<<< orphan*/  rq_cred; scalar_t__ rq_auth_slack; TYPE_1__ rq_arg; } ;
struct auth_ops {int (* accept ) (struct svc_rqst*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int SVC_DENIED ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_svc_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_auth_ok ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int stub1 (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 struct auth_ops* svc_get_auth_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_getnl (int /*<<< orphan*/ *) ; 

int
svc_authenticate(struct svc_rqst *rqstp, __be32 *authp)
{
	rpc_authflavor_t	flavor;
	struct auth_ops		*aops;

	*authp = rpc_auth_ok;

	flavor = svc_getnl(&rqstp->rq_arg.head[0]);

	dprintk("svc: svc_authenticate (%d)\n", flavor);

	aops = svc_get_auth_ops(flavor);
	if (aops == NULL) {
		*authp = rpc_autherr_badcred;
		return SVC_DENIED;
	}

	rqstp->rq_auth_slack = 0;
	init_svc_cred(&rqstp->rq_cred);

	rqstp->rq_authop = aops;
	return aops->accept(rqstp, authp);
}