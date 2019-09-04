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
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {struct rpc_clnt* cl_parent; scalar_t__ cl_autobind; TYPE_1__ cl_xpi; } ;

/* Variables and functions */
 struct rpc_xprt_switch* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_clnt *rpcb_find_transport_owner(struct rpc_clnt *clnt)
{
	struct rpc_clnt *parent = clnt->cl_parent;
	struct rpc_xprt_switch *xps = rcu_access_pointer(clnt->cl_xpi.xpi_xpswitch);

	while (parent != clnt) {
		if (rcu_access_pointer(parent->cl_xpi.xpi_xpswitch) != xps)
			break;
		if (clnt->cl_autobind)
			break;
		clnt = parent;
		parent = parent->cl_parent;
	}
	return clnt;
}