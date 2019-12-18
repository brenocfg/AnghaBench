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
struct TYPE_2__ {int /*<<< orphan*/  (* bc_destroy ) (struct rpc_xprt*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,unsigned int) ; 

void xprt_destroy_backchannel(struct rpc_xprt *xprt, unsigned int max_reqs)
{
	if (xprt->ops->bc_destroy)
		xprt->ops->bc_destroy(xprt, max_reqs);
}