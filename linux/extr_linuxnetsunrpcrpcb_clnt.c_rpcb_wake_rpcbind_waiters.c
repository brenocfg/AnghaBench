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
struct rpc_xprt {int /*<<< orphan*/  binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_wake_up_status (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xprt_clear_binding (struct rpc_xprt*) ; 

__attribute__((used)) static void rpcb_wake_rpcbind_waiters(struct rpc_xprt *xprt, int status)
{
	xprt_clear_binding(xprt);
	rpc_wake_up_status(&xprt->binding, status);
}