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
struct rpc_task {scalar_t__ tk_status; int /*<<< orphan*/  tk_start; scalar_t__ tk_timeouts; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_rtt; int /*<<< orphan*/  rq_task; scalar_t__ rq_xtime; scalar_t__ rq_reply_bytes_recvd; scalar_t__ rq_xmit_bytes_sent; int /*<<< orphan*/  rq_ntrans; } ;
struct rpc_iostats {int /*<<< orphan*/  om_lock; int /*<<< orphan*/  om_error_status; void* om_execute; void* om_rtt; void* om_queue; int /*<<< orphan*/  om_bytes_recv; int /*<<< orphan*/  om_bytes_sent; int /*<<< orphan*/  om_timeouts; int /*<<< orphan*/  om_ntrans; int /*<<< orphan*/  om_ops; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 void* ktime_add (void*,scalar_t__) ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_sub (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (scalar_t__) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rpc_stats_latency (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

void rpc_count_iostats_metrics(const struct rpc_task *task,
			       struct rpc_iostats *op_metrics)
{
	struct rpc_rqst *req = task->tk_rqstp;
	ktime_t backlog, execute, now;

	if (!op_metrics || !req)
		return;

	now = ktime_get();
	spin_lock(&op_metrics->om_lock);

	op_metrics->om_ops++;
	/* kernel API: om_ops must never become larger than om_ntrans */
	op_metrics->om_ntrans += max(req->rq_ntrans, 1);
	op_metrics->om_timeouts += task->tk_timeouts;

	op_metrics->om_bytes_sent += req->rq_xmit_bytes_sent;
	op_metrics->om_bytes_recv += req->rq_reply_bytes_recvd;

	backlog = 0;
	if (ktime_to_ns(req->rq_xtime)) {
		backlog = ktime_sub(req->rq_xtime, task->tk_start);
		op_metrics->om_queue = ktime_add(op_metrics->om_queue, backlog);
	}

	op_metrics->om_rtt = ktime_add(op_metrics->om_rtt, req->rq_rtt);

	execute = ktime_sub(now, task->tk_start);
	op_metrics->om_execute = ktime_add(op_metrics->om_execute, execute);
	if (task->tk_status < 0)
		op_metrics->om_error_status++;

	spin_unlock(&op_metrics->om_lock);

	trace_rpc_stats_latency(req->rq_task, backlog, req->rq_rtt, execute);
}