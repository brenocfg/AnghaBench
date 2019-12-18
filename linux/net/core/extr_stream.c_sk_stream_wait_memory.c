#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_shutdown; TYPE_1__* sk_socket; int /*<<< orphan*/  sk_write_pending; scalar_t__ sk_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EPIPE ; 
 int HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ sk_stream_memory_free (struct sock*) ; 
 int /*<<< orphan*/  sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

int sk_stream_wait_memory(struct sock *sk, long *timeo_p)
{
	int err = 0;
	long vm_wait = 0;
	long current_timeo = *timeo_p;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	if (sk_stream_memory_free(sk))
		current_timeo = vm_wait = (prandom_u32() % (HZ / 5)) + 2;

	add_wait_queue(sk_sleep(sk), &wait);

	while (1) {
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

		if (sk->sk_err || (sk->sk_shutdown & SEND_SHUTDOWN))
			goto do_error;
		if (!*timeo_p)
			goto do_eagain;
		if (signal_pending(current))
			goto do_interrupted;
		sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		if (sk_stream_memory_free(sk) && !vm_wait)
			break;

		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk->sk_write_pending++;
		sk_wait_event(sk, &current_timeo, sk->sk_err ||
						  (sk->sk_shutdown & SEND_SHUTDOWN) ||
						  (sk_stream_memory_free(sk) &&
						  !vm_wait), &wait);
		sk->sk_write_pending--;

		if (vm_wait) {
			vm_wait -= current_timeo;
			current_timeo = *timeo_p;
			if (current_timeo != MAX_SCHEDULE_TIMEOUT &&
			    (current_timeo -= vm_wait) < 0)
				current_timeo = 0;
			vm_wait = 0;
		}
		*timeo_p = current_timeo;
	}
out:
	remove_wait_queue(sk_sleep(sk), &wait);
	return err;

do_error:
	err = -EPIPE;
	goto out;
do_eagain:
	/* Make sure that whenever EAGAIN is returned, EPOLLOUT event can
	 * be generated later.
	 * When TCP receives ACK packets that make room, tcp_check_space()
	 * only calls tcp_new_space() if SOCK_NOSPACE is set.
	 */
	set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
	err = -EAGAIN;
	goto out;
do_interrupted:
	err = sock_intr_errno(*timeo_p);
	goto out;
}