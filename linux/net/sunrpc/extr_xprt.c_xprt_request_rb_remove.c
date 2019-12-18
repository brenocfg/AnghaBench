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
struct rpc_xprt {int /*<<< orphan*/  recv_queue; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_request_rb_remove(struct rpc_xprt *xprt, struct rpc_rqst *req)
{
	rb_erase(&req->rq_recv, &xprt->recv_queue);
}