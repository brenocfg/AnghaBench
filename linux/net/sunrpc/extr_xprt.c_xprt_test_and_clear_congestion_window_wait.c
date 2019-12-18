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
struct rpc_xprt {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCXPRT_CONGESTED (struct rpc_xprt*) ; 
 int /*<<< orphan*/  XPRT_CWND_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_test_and_clear_congestion_window_wait(struct rpc_xprt *xprt)
{
	if (!RPCXPRT_CONGESTED(xprt))
		clear_bit(XPRT_CWND_WAIT, &xprt->state);
}