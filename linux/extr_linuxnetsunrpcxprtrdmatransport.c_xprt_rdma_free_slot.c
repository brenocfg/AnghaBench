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
struct rpc_xprt {int /*<<< orphan*/  backlog; } ;
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct rpc_rqst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_wake_up_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_buffer_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xprt_rdma_free_slot(struct rpc_xprt *xprt, struct rpc_rqst *rqst)
{
	memset(rqst, 0, sizeof(*rqst));
	rpcrdma_buffer_put(rpcr_to_rdmar(rqst));
	rpc_wake_up_next(&xprt->backlog);
}