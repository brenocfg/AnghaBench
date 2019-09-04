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
struct rpc_xprt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {TYPE_1__ cl_xpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rpc_xprt_switch_add_xprt (int /*<<< orphan*/ ,struct rpc_xprt*) ; 

void rpc_clnt_xprt_switch_add_xprt(struct rpc_clnt *clnt, struct rpc_xprt *xprt)
{
	rcu_read_lock();
	rpc_xprt_switch_add_xprt(rcu_dereference(clnt->cl_xpi.xpi_xpswitch),
				 xprt);
	rcu_read_unlock();
}