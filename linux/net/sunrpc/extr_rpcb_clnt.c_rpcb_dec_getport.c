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
struct rpcbind_args {unsigned long r_port; } ;
struct rpc_rqst {TYPE_3__* rq_task; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {TYPE_1__* rpc_proc; } ;
struct TYPE_6__ {TYPE_2__ tk_msg; int /*<<< orphan*/  tk_pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long USHRT_MAX ; 
 unsigned long be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int rpcb_dec_getport(struct rpc_rqst *req, struct xdr_stream *xdr,
			    void *data)
{
	struct rpcbind_args *rpcb = data;
	unsigned long port;
	__be32 *p;

	rpcb->r_port = 0;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		return -EIO;

	port = be32_to_cpup(p);
	dprintk("RPC: %5u PMAP_%s result: %lu\n", req->rq_task->tk_pid,
			req->rq_task->tk_msg.rpc_proc->p_name, port);
	if (unlikely(port > USHRT_MAX))
		return -EIO;

	rpcb->r_port = port;
	return 0;
}