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
struct sock_xprt {int /*<<< orphan*/  recv_worker; int /*<<< orphan*/  sock_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_SOCK_DATA_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprtiod_workqueue ; 
 int /*<<< orphan*/  xs_poll_socket_readable (struct sock_xprt*) ; 

__attribute__((used)) static void xs_poll_check_readable(struct sock_xprt *transport)
{

	clear_bit(XPRT_SOCK_DATA_READY, &transport->sock_state);
	if (!xs_poll_socket_readable(transport))
		return;
	if (!test_and_set_bit(XPRT_SOCK_DATA_READY, &transport->sock_state))
		queue_work(xprtiod_workqueue, &transport->recv_worker);
}