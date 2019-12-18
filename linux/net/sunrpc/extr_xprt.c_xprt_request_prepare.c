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
struct rpc_xprt {TYPE_1__* ops; } ;
struct rpc_rqst {struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prepare_request ) (struct rpc_rqst*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_rqst*) ; 

void
xprt_request_prepare(struct rpc_rqst *req)
{
	struct rpc_xprt *xprt = req->rq_xprt;

	if (xprt->ops->prepare_request)
		xprt->ops->prepare_request(req);
}