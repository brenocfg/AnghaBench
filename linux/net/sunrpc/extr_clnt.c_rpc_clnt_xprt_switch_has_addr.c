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
struct sockaddr {int dummy; } ;
struct rpc_xprt_switch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {TYPE_1__ cl_xpi; } ;

/* Variables and functions */
 struct rpc_xprt_switch* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rpc_xprt_switch_has_addr (struct rpc_xprt_switch*,struct sockaddr const*) ; 

bool rpc_clnt_xprt_switch_has_addr(struct rpc_clnt *clnt,
				   const struct sockaddr *sap)
{
	struct rpc_xprt_switch *xps;
	bool ret;

	rcu_read_lock();
	xps = rcu_dereference(clnt->cl_xpi.xpi_xpswitch);
	ret = rpc_xprt_switch_has_addr(xps, sap);
	rcu_read_unlock();
	return ret;
}