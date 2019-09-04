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
struct TYPE_2__ {int /*<<< orphan*/  (* xpi_rewind ) (struct rpc_xprt_iter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt_iter*) ; 
 TYPE_1__* xprt_iter_ops (struct rpc_xprt_iter*) ; 

__attribute__((used)) static
void xprt_iter_rewind(struct rpc_xprt_iter *xpi)
{
	rcu_read_lock();
	xprt_iter_ops(xpi)->xpi_rewind(xpi);
	rcu_read_unlock();
}