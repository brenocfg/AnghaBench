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
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int RPCRDMA_BACKWARD_WRS ; 

unsigned int xprt_rdma_bc_max_slots(struct rpc_xprt *xprt)
{
	return RPCRDMA_BACKWARD_WRS >> 1;
}