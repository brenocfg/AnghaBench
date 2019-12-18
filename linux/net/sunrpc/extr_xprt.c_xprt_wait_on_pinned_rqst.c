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
struct rpc_rqst {int /*<<< orphan*/  rq_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xprt_is_pinned_rqst (struct rpc_rqst*) ; 

__attribute__((used)) static void xprt_wait_on_pinned_rqst(struct rpc_rqst *req)
{
	wait_var_event(&req->rq_pin, !xprt_is_pinned_rqst(req));
}