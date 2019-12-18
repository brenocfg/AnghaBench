#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_4__ {TYPE_1__* ep; } ;
struct TYPE_3__ {int /*<<< orphan*/  asocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  LISTENING ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 TYPE_2__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_sstate (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int sctp_wait_for_packet(struct sock *sk, int *err, long *timeo_p)
{
	int error;
	DEFINE_WAIT(wait);

	prepare_to_wait_exclusive(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);

	/* Socket errors? */
	error = sock_error(sk);
	if (error)
		goto out;

	if (!skb_queue_empty(&sk->sk_receive_queue))
		goto ready;

	/* Socket shut down?  */
	if (sk->sk_shutdown & RCV_SHUTDOWN)
		goto out;

	/* Sequenced packets can come disconnected.  If so we report the
	 * problem.
	 */
	error = -ENOTCONN;

	/* Is there a good reason to think that we may receive some data?  */
	if (list_empty(&sctp_sk(sk)->ep->asocs) && !sctp_sstate(sk, LISTENING))
		goto out;

	/* Handle signals.  */
	if (signal_pending(current))
		goto interrupted;

	/* Let another process have a go.  Since we are going to sleep
	 * anyway.  Note: This may cause odd behaviors if the message
	 * does not fit in the user's buffer, but this seems to be the
	 * only way to honor MSG_DONTWAIT realistically.
	 */
	release_sock(sk);
	*timeo_p = schedule_timeout(*timeo_p);
	lock_sock(sk);

ready:
	finish_wait(sk_sleep(sk), &wait);
	return 0;

interrupted:
	error = sock_intr_errno(*timeo_p);

out:
	finish_wait(sk_sleep(sk), &wait);
	*err = error;
	return error;
}