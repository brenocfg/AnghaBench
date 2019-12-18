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
struct sock_xprt {int /*<<< orphan*/  recv_mutex; int /*<<< orphan*/  xprt; int /*<<< orphan*/  xprt_err; int /*<<< orphan*/  sock_state; int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_SOCK_WAKE_ERROR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_wake_pending_tasks (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void xs_wake_error(struct sock_xprt *transport)
{
	int sockerr;

	if (!test_bit(XPRT_SOCK_WAKE_ERROR, &transport->sock_state))
		return;
	mutex_lock(&transport->recv_mutex);
	if (transport->sock == NULL)
		goto out;
	if (!test_and_clear_bit(XPRT_SOCK_WAKE_ERROR, &transport->sock_state))
		goto out;
	sockerr = xchg(&transport->xprt_err, 0);
	if (sockerr < 0)
		xprt_wake_pending_tasks(&transport->xprt, sockerr);
out:
	mutex_unlock(&transport->recv_mutex);
}