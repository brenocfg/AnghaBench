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
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  XPRT_CLOSING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  xs_sock_reset_state_flags (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_sock_reset_connection_flags(struct rpc_xprt *xprt)
{
	smp_mb__before_atomic();
	clear_bit(XPRT_CLOSE_WAIT, &xprt->state);
	clear_bit(XPRT_CLOSING, &xprt->state);
	xs_sock_reset_state_flags(xprt);
	smp_mb__after_atomic();
}