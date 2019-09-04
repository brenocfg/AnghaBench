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
struct svc_rqst {int /*<<< orphan*/  rq_proc; TYPE_1__* rq_authop; } ;
struct TYPE_2__ {int flavour; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB_NULL ; 
#define  RPC_AUTH_GSS 129 
#define  RPC_AUTH_NULL 128 
 int SVC_DENIED ; 
 int SVC_OK ; 
 int /*<<< orphan*/  svc_is_backchannel (struct svc_rqst*) ; 

__attribute__((used)) static int nfs_callback_authenticate(struct svc_rqst *rqstp)
{
	switch (rqstp->rq_authop->flavour) {
	case RPC_AUTH_NULL:
		if (rqstp->rq_proc != CB_NULL)
			return SVC_DENIED;
		break;
	case RPC_AUTH_GSS:
		/* No RPC_AUTH_GSS support yet in NFSv4.1 */
		 if (svc_is_backchannel(rqstp))
			return SVC_DENIED;
	}
	return SVC_OK;
}