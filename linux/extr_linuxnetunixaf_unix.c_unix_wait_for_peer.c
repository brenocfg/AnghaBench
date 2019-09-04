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
struct unix_sock {int /*<<< orphan*/  peer_wait; } ;
struct sock {int sk_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unix_recvq_full (struct sock*) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static long unix_wait_for_peer(struct sock *other, long timeo)
{
	struct unix_sock *u = unix_sk(other);
	int sched;
	DEFINE_WAIT(wait);

	prepare_to_wait_exclusive(&u->peer_wait, &wait, TASK_INTERRUPTIBLE);

	sched = !sock_flag(other, SOCK_DEAD) &&
		!(other->sk_shutdown & RCV_SHUTDOWN) &&
		unix_recvq_full(other);

	unix_state_unlock(other);

	if (sched)
		timeo = schedule_timeout(timeo);

	finish_wait(&u->peer_wait, &wait);
	return timeo;
}