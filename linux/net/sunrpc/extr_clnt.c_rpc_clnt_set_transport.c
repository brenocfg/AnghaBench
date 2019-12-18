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
struct rpc_timeout {int dummy; } ;
struct rpc_clnt {int cl_autobind; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_xprt; struct rpc_timeout const* cl_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct rpc_xprt*) ; 
 struct rpc_xprt* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_bound (struct rpc_xprt*) ; 

__attribute__((used)) static struct rpc_xprt *rpc_clnt_set_transport(struct rpc_clnt *clnt,
		struct rpc_xprt *xprt,
		const struct rpc_timeout *timeout)
{
	struct rpc_xprt *old;

	spin_lock(&clnt->cl_lock);
	old = rcu_dereference_protected(clnt->cl_xprt,
			lockdep_is_held(&clnt->cl_lock));

	if (!xprt_bound(xprt))
		clnt->cl_autobind = 1;

	clnt->cl_timeout = timeout;
	rcu_assign_pointer(clnt->cl_xprt, xprt);
	spin_unlock(&clnt->cl_lock);

	return old;
}