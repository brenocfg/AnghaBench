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
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt_iter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {TYPE_1__ cl_xpi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  xprt_iter_init_listall (struct rpc_xprt_iter*,struct rpc_xprt_switch*) ; 
 struct rpc_xprt_switch* xprt_switch_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_switch_put (struct rpc_xprt_switch*) ; 

__attribute__((used)) static
int rpc_clnt_xprt_iter_init(struct rpc_clnt *clnt, struct rpc_xprt_iter *xpi)
{
	struct rpc_xprt_switch *xps;

	rcu_read_lock();
	xps = xprt_switch_get(rcu_dereference(clnt->cl_xpi.xpi_xpswitch));
	rcu_read_unlock();
	if (xps == NULL)
		return -EAGAIN;
	xprt_iter_init_listall(xpi, xps);
	xprt_switch_put(xps);
	return 0;
}