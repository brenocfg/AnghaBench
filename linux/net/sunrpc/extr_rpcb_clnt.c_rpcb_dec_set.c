#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct rpc_rqst {TYPE_2__* rq_task; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  p_name; } ;
struct TYPE_4__ {TYPE_3__* rpc_proc; } ;
struct TYPE_5__ {TYPE_1__ tk_msg; int /*<<< orphan*/  tk_pid; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static int rpcb_dec_set(struct rpc_rqst *req, struct xdr_stream *xdr,
			void *data)
{
	unsigned int *boolp = data;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		return -EIO;

	*boolp = 0;
	if (*p != xdr_zero)
		*boolp = 1;

	dprintk("RPC: %5u RPCB_%s call %s\n",
			req->rq_task->tk_pid,
			req->rq_task->tk_msg.rpc_proc->p_name,
			(*boolp ? "succeeded" : "failed"));
	return 0;
}