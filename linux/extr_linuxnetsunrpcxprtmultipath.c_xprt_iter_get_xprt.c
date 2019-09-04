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
struct rpc_xprt_iter {int dummy; } ;
struct rpc_xprt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rpc_xprt* xprt_iter_get_helper (struct rpc_xprt_iter*,int /*<<< orphan*/ ) ; 
 TYPE_1__* xprt_iter_ops (struct rpc_xprt_iter*) ; 

struct rpc_xprt *xprt_iter_get_xprt(struct rpc_xprt_iter *xpi)
{
	struct rpc_xprt *xprt;

	rcu_read_lock();
	xprt = xprt_iter_get_helper(xpi, xprt_iter_ops(xpi)->xpi_xprt);
	rcu_read_unlock();
	return xprt;
}