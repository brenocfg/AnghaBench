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
struct TYPE_2__ {struct rpc_xprt* (* xpi_xprt ) (struct rpc_xprt_iter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 struct rpc_xprt* stub1 (struct rpc_xprt_iter*) ; 
 TYPE_1__* xprt_iter_ops (struct rpc_xprt_iter*) ; 

struct rpc_xprt *xprt_iter_xprt(struct rpc_xprt_iter *xpi)
{
	WARN_ON_ONCE(!rcu_read_lock_held());
	return xprt_iter_ops(xpi)->xpi_xprt(xpi);
}