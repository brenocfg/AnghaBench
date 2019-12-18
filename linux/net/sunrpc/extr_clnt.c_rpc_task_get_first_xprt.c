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
struct rpc_clnt {int /*<<< orphan*/  cl_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rpc_xprt* rpc_task_get_xprt (struct rpc_clnt*,struct rpc_xprt*) ; 
 struct rpc_xprt* xprt_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_xprt *
rpc_task_get_first_xprt(struct rpc_clnt *clnt)
{
	struct rpc_xprt *xprt;

	rcu_read_lock();
	xprt = xprt_get(rcu_dereference(clnt->cl_xprt));
	rcu_read_unlock();
	return rpc_task_get_xprt(clnt, xprt);
}