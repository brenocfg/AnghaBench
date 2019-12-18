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
struct svc_rqst {int /*<<< orphan*/  rq_flags; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_AUTHERR ; 
 int /*<<< orphan*/  rpc_auth_ok ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
svc_get_autherr(struct svc_rqst *rqstp, __be32 *statp)
{
	if (test_and_clear_bit(RQ_AUTHERR, &rqstp->rq_flags))
		return *statp;
	return rpc_auth_ok;
}