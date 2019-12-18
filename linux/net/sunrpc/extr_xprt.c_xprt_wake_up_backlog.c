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
struct rpc_xprt {int /*<<< orphan*/  state; int /*<<< orphan*/  backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CONGESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rpc_wake_up_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xprt_wake_up_backlog(struct rpc_xprt *xprt)
{
	if (rpc_wake_up_next(&xprt->backlog) == NULL)
		clear_bit(XPRT_CONGESTED, &xprt->state);
}