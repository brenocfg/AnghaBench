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
struct rpc_xprt {int reestablish_timeout; int max_reconnect_timeout; } ;

/* Variables and functions */
 int XS_TCP_INIT_REEST_TO ; 

__attribute__((used)) static void xs_reconnect_backoff(struct rpc_xprt *xprt)
{
	xprt->reestablish_timeout <<= 1;
	if (xprt->reestablish_timeout > xprt->max_reconnect_timeout)
		xprt->reestablish_timeout = xprt->max_reconnect_timeout;
	if (xprt->reestablish_timeout < XS_TCP_INIT_REEST_TO)
		xprt->reestablish_timeout = XS_TCP_INIT_REEST_TO;
}