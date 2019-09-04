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
struct TYPE_2__ {scalar_t__ cr_flavor; } ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; TYPE_1__ rq_cred; } ;

/* Variables and functions */
 int NFSEXP_INSECURE_PORT ; 
 scalar_t__ RPC_AUTH_GSS ; 
 int /*<<< orphan*/  RQ_SECURE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfsd_originating_port_ok(struct svc_rqst *rqstp, int flags)
{
	if (flags & NFSEXP_INSECURE_PORT)
		return true;
	/* We don't require gss requests to use low ports: */
	if (rqstp->rq_cred.cr_flavor >= RPC_AUTH_GSS)
		return true;
	return test_bit(RQ_SECURE, &rqstp->rq_flags);
}