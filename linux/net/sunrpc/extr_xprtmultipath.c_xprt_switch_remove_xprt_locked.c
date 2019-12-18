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
struct rpc_xprt_switch {scalar_t__ xps_nxprts; int /*<<< orphan*/ * xps_net; int /*<<< orphan*/  xps_nactive; } ;
struct rpc_xprt {int /*<<< orphan*/  xprt_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xprt_switch_remove_xprt_locked(struct rpc_xprt_switch *xps,
		struct rpc_xprt *xprt)
{
	if (unlikely(xprt == NULL))
		return;
	xps->xps_nactive--;
	xps->xps_nxprts--;
	if (xps->xps_nxprts == 0)
		xps->xps_net = NULL;
	smp_wmb();
	list_del_rcu(&xprt->xprt_switch);
}