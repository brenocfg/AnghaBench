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
struct TYPE_4__ {int /*<<< orphan*/  rpc_resp; TYPE_1__* rpc_proc; } ;
struct rpc_task {TYPE_2__ tk_msg; int /*<<< orphan*/  tk_rqstp; } ;
typedef  int (* kxdrdproc_t ) (int /*<<< orphan*/ ,struct xdr_stream*,int /*<<< orphan*/ ) ;
struct TYPE_3__ {int (* p_decode ) (int /*<<< orphan*/ ,struct xdr_stream*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */

int
rpcauth_unwrap_resp_decode(struct rpc_task *task, struct xdr_stream *xdr)
{
	kxdrdproc_t decode = task->tk_msg.rpc_proc->p_decode;

	return decode(task->tk_rqstp, xdr, task->tk_msg.rpc_resp);
}