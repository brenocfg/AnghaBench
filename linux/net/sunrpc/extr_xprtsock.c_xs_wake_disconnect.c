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
struct sock_xprt {int /*<<< orphan*/  xprt; int /*<<< orphan*/  sock_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_SOCK_WAKE_DISCONNECT ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_tcp_force_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xs_wake_disconnect(struct sock_xprt *transport)
{
	if (test_and_clear_bit(XPRT_SOCK_WAKE_DISCONNECT, &transport->sock_state))
		xs_tcp_force_close(&transport->xprt);
}