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
typedef  scalar_t__ u32 ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_seqno; struct rpc_cred* rq_cred; } ;
struct rpc_cred {int dummy; } ;
struct gss_cl_ctx {scalar_t__ gc_win; int /*<<< orphan*/  gc_seq_xmit; int /*<<< orphan*/  gc_seq; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 struct gss_cl_ctx* gss_cred_get_ctx (struct rpc_cred*) ; 
 int /*<<< orphan*/  gss_put_ctx (struct gss_cl_ctx*) ; 
 scalar_t__ gss_seq_is_newer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_rpcgss_need_reencode (struct rpc_task*,scalar_t__,int) ; 

__attribute__((used)) static bool
gss_xmit_need_reencode(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_cred *cred = req->rq_cred;
	struct gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	u32 win, seq_xmit = 0;
	bool ret = true;

	if (!ctx)
		goto out;

	if (gss_seq_is_newer(req->rq_seqno, READ_ONCE(ctx->gc_seq)))
		goto out_ctx;

	seq_xmit = READ_ONCE(ctx->gc_seq_xmit);
	while (gss_seq_is_newer(req->rq_seqno, seq_xmit)) {
		u32 tmp = seq_xmit;

		seq_xmit = cmpxchg(&ctx->gc_seq_xmit, tmp, req->rq_seqno);
		if (seq_xmit == tmp) {
			ret = false;
			goto out_ctx;
		}
	}

	win = ctx->gc_win;
	if (win > 0)
		ret = !gss_seq_is_newer(req->rq_seqno, seq_xmit - win);

out_ctx:
	gss_put_ctx(ctx);
out:
	trace_rpcgss_need_reencode(task, seq_xmit, ret);
	return ret;
}