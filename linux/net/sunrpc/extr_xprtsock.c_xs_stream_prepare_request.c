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
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; TYPE_1__* rq_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  tk_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  xdr_alloc_bvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_free_bvec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xs_stream_prepare_request(struct rpc_rqst *req)
{
	xdr_free_bvec(&req->rq_rcv_buf);
	req->rq_task->tk_status = xdr_alloc_bvec(&req->rq_rcv_buf, GFP_KERNEL);
}