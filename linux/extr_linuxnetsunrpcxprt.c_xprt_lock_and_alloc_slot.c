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
struct rpc_xprt {int dummy; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xprt_alloc_slot (struct rpc_xprt*,struct rpc_task*) ; 
 scalar_t__ xprt_lock_write (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_release_write (struct rpc_xprt*,struct rpc_task*) ; 

void xprt_lock_and_alloc_slot(struct rpc_xprt *xprt, struct rpc_task *task)
{
	/* Note: grabbing the xprt_lock_write() ensures that we throttle
	 * new slot allocation if the transport is congested (i.e. when
	 * reconnecting a stream transport or when out of socket write
	 * buffer space).
	 */
	if (xprt_lock_write(xprt, task)) {
		xprt_alloc_slot(xprt, task);
		xprt_release_write(xprt, task);
	}
}