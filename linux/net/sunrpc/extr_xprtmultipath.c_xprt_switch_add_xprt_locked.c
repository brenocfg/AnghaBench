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
struct rpc_xprt_switch {scalar_t__ xps_nxprts; int /*<<< orphan*/  xps_nactive; int /*<<< orphan*/  xps_net; int /*<<< orphan*/  xps_xprt_list; } ;
struct rpc_xprt {int /*<<< orphan*/  xprt_net; int /*<<< orphan*/  xprt_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xprt_get (struct rpc_xprt*) ; 

__attribute__((used)) static void xprt_switch_add_xprt_locked(struct rpc_xprt_switch *xps,
		struct rpc_xprt *xprt)
{
	if (unlikely(xprt_get(xprt) == NULL))
		return;
	list_add_tail_rcu(&xprt->xprt_switch, &xps->xps_xprt_list);
	smp_wmb();
	if (xps->xps_nxprts == 0)
		xps->xps_net = xprt->xprt_net;
	xps->xps_nxprts++;
	xps->xps_nactive++;
}