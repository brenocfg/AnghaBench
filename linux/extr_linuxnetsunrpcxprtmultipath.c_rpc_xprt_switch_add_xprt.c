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
struct sockaddr {int dummy; } ;
struct rpc_xprt_switch {int /*<<< orphan*/  xps_lock; int /*<<< orphan*/ * xps_net; } ;
struct rpc_xprt {int /*<<< orphan*/  addr; int /*<<< orphan*/ * xprt_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_xprt_switch_has_addr (struct rpc_xprt_switch*,struct sockaddr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_switch_add_xprt_locked (struct rpc_xprt_switch*,struct rpc_xprt*) ; 

void rpc_xprt_switch_add_xprt(struct rpc_xprt_switch *xps,
		struct rpc_xprt *xprt)
{
	if (xprt == NULL)
		return;
	spin_lock(&xps->xps_lock);
	if ((xps->xps_net == xprt->xprt_net || xps->xps_net == NULL) &&
	    !rpc_xprt_switch_has_addr(xps, (struct sockaddr *)&xprt->addr))
		xprt_switch_add_xprt_locked(xps, xprt);
	spin_unlock(&xps->xps_lock);
}