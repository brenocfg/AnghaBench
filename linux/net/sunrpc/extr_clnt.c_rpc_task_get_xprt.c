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
struct rpc_xprt_switch {int /*<<< orphan*/  xps_queuelen; } ;
struct rpc_xprt {int /*<<< orphan*/  queuelen; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {TYPE_1__ cl_xpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct rpc_xprt_switch* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct rpc_xprt *
rpc_task_get_xprt(struct rpc_clnt *clnt, struct rpc_xprt *xprt)
{
	struct rpc_xprt_switch *xps;

	if (!xprt)
		return NULL;
	rcu_read_lock();
	xps = rcu_dereference(clnt->cl_xpi.xpi_xpswitch);
	atomic_long_inc(&xps->xps_queuelen);
	rcu_read_unlock();
	atomic_long_inc(&xprt->queuelen);

	return xprt;
}