#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct rpc_task {TYPE_2__* tk_rqstp; } ;
struct rpc_credops {int (* crvalidate ) (struct rpc_task*,struct xdr_stream*) ;} ;
struct TYPE_4__ {TYPE_1__* rq_cred; } ;
struct TYPE_3__ {struct rpc_credops* cr_ops; } ;

/* Variables and functions */
 int stub1 (struct rpc_task*,struct xdr_stream*) ; 

int
rpcauth_checkverf(struct rpc_task *task, struct xdr_stream *xdr)
{
	const struct rpc_credops *ops = task->tk_rqstp->rq_cred->cr_ops;

	return ops->crvalidate(task, xdr);
}