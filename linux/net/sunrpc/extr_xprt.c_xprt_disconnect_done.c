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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_clear_congestion_window_wait_locked (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_clear_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_clear_write_space_locked (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_wake_pending_tasks (struct rpc_xprt*,int /*<<< orphan*/ ) ; 

void xprt_disconnect_done(struct rpc_xprt *xprt)
{
	dprintk("RPC:       disconnected transport %p\n", xprt);
	spin_lock(&xprt->transport_lock);
	xprt_clear_connected(xprt);
	xprt_clear_write_space_locked(xprt);
	xprt_clear_congestion_window_wait_locked(xprt);
	xprt_wake_pending_tasks(xprt, -ENOTCONN);
	spin_unlock(&xprt->transport_lock);
}