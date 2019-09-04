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
struct rpc_clnt {int /*<<< orphan*/  cl_xprt; scalar_t__ cl_autobind; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  xprt_clear_bound (int /*<<< orphan*/ ) ; 

void rpc_force_rebind(struct rpc_clnt *clnt)
{
	if (clnt->cl_autobind) {
		rcu_read_lock();
		xprt_clear_bound(rcu_dereference(clnt->cl_xprt));
		rcu_read_unlock();
	}
}