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
struct svc_rqst {int /*<<< orphan*/  rq_proc; TYPE_1__* rq_authop; int /*<<< orphan*/ * rq_client; } ;
struct TYPE_2__ {int flavour; } ;

/* Variables and functions */
#define  RPC_AUTH_NULL 129 
#define  RPC_AUTH_UNIX 128 
 int SVC_DENIED ; 
 int SVC_OK ; 
 int /*<<< orphan*/  is_callback (int /*<<< orphan*/ ) ; 
 int svc_set_client (struct svc_rqst*) ; 

__attribute__((used)) static int lockd_authenticate(struct svc_rqst *rqstp)
{
	rqstp->rq_client = NULL;
	switch (rqstp->rq_authop->flavour) {
		case RPC_AUTH_NULL:
		case RPC_AUTH_UNIX:
			if (rqstp->rq_proc == 0)
				return SVC_OK;
			if (is_callback(rqstp->rq_proc)) {
				/* Leave it to individual procedures to
				 * call nlmsvc_lookup_host(rqstp)
				 */
				return SVC_OK;
			}
			return svc_set_client(rqstp);
	}
	return SVC_DENIED;
}