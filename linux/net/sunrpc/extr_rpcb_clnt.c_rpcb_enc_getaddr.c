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
struct rpcbind_args {int /*<<< orphan*/  r_owner; int /*<<< orphan*/  r_addr; int /*<<< orphan*/  r_netid; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
struct rpc_rqst {TYPE_3__* rq_task; } ;
typedef  void* __be32 ;
struct TYPE_5__ {TYPE_1__* rpc_proc; } ;
struct TYPE_6__ {TYPE_2__ tk_msg; int /*<<< orphan*/  tk_pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCBIND_MAXNETIDLEN ; 
 int /*<<< orphan*/  RPCBIND_MAXUADDRLEN ; 
 int /*<<< orphan*/  RPCB_MAXOWNERLEN ; 
 int RPCB_program_sz ; 
 int RPCB_version_sz ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_rpcb_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void rpcb_enc_getaddr(struct rpc_rqst *req, struct xdr_stream *xdr,
			     const void *data)
{
	const struct rpcbind_args *rpcb = data;
	__be32 *p;

	dprintk("RPC: %5u encoding RPCB_%s call (%u, %u, '%s', '%s')\n",
			req->rq_task->tk_pid,
			req->rq_task->tk_msg.rpc_proc->p_name,
			rpcb->r_prog, rpcb->r_vers,
			rpcb->r_netid, rpcb->r_addr);

	p = xdr_reserve_space(xdr, (RPCB_program_sz + RPCB_version_sz) << 2);
	*p++ = cpu_to_be32(rpcb->r_prog);
	*p = cpu_to_be32(rpcb->r_vers);

	encode_rpcb_string(xdr, rpcb->r_netid, RPCBIND_MAXNETIDLEN);
	encode_rpcb_string(xdr, rpcb->r_addr, RPCBIND_MAXUADDRLEN);
	encode_rpcb_string(xdr, rpcb->r_owner, RPCB_MAXOWNERLEN);
}