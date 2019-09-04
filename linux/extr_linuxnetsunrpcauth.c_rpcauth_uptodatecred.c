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
struct rpc_task {TYPE_1__* tk_rqstp; } ;
struct rpc_cred {int /*<<< orphan*/  cr_flags; } ;
struct TYPE_2__ {struct rpc_cred* rq_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
rpcauth_uptodatecred(struct rpc_task *task)
{
	struct rpc_cred *cred = task->tk_rqstp->rq_cred;

	return cred == NULL ||
		test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0;
}