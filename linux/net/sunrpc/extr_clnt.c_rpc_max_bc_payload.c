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
struct rpc_clnt {int /*<<< orphan*/  cl_xprt; } ;
struct TYPE_2__ {size_t (* bc_maxpayload ) (struct rpc_xprt*) ;} ;

/* Variables and functions */
 struct rpc_xprt* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 size_t stub1 (struct rpc_xprt*) ; 

size_t rpc_max_bc_payload(struct rpc_clnt *clnt)
{
	struct rpc_xprt *xprt;
	size_t ret;

	rcu_read_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	ret = xprt->ops->bc_maxpayload(xprt);
	rcu_read_unlock();
	return ret;
}