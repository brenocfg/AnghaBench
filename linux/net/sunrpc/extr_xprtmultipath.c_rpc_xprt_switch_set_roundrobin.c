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
struct rpc_xprt_switch {int /*<<< orphan*/  xps_iter_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/ * READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_xprt_iter_roundrobin ; 

void rpc_xprt_switch_set_roundrobin(struct rpc_xprt_switch *xps)
{
	if (READ_ONCE(xps->xps_iter_ops) != &rpc_xprt_iter_roundrobin)
		WRITE_ONCE(xps->xps_iter_ops, &rpc_xprt_iter_roundrobin);
}