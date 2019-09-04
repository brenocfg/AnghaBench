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
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_SYN_SENT ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static bool llc_ui_wait_for_conn(struct sock *sk, long timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(sk_sleep(sk), &wait);
	while (1) {
		if (sk_wait_event(sk, &timeout, sk->sk_state != TCP_SYN_SENT, &wait))
			break;
		if (signal_pending(current) || !timeout)
			break;
	}
	remove_wait_queue(sk_sleep(sk), &wait);
	return timeout;
}