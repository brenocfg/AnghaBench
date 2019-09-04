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
struct rpc_task {scalar_t__ tk_status; TYPE_1__* tk_rqstp; } ;
struct nfs4_setclientid {int /*<<< orphan*/  sc_cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rpccred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_setclientid_done(struct rpc_task *task, void *calldata)
{
	struct nfs4_setclientid *sc = calldata;

	if (task->tk_status == 0)
		sc->sc_cred = get_rpccred(task->tk_rqstp->rq_cred);
}