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
struct task_struct {int dummy; } ;
struct sock {int sk_state; int /*<<< orphan*/  sk_write_pending; int /*<<< orphan*/  sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EPIPE ; 
 int TCPF_CLOSE_WAIT ; 
 int TCPF_ESTABLISHED ; 
 int TCPF_SYN_RECV ; 
 int TCPF_SYN_SENT ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

int sk_stream_wait_connect(struct sock *sk, long *timeo_p)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct task_struct *tsk = current;
	int done;

	do {
		int err = sock_error(sk);
		if (err)
			return err;
		if ((1 << sk->sk_state) & ~(TCPF_SYN_SENT | TCPF_SYN_RECV))
			return -EPIPE;
		if (!*timeo_p)
			return -EAGAIN;
		if (signal_pending(tsk))
			return sock_intr_errno(*timeo_p);

		add_wait_queue(sk_sleep(sk), &wait);
		sk->sk_write_pending++;
		done = sk_wait_event(sk, timeo_p,
				     !sk->sk_err &&
				     !((1 << sk->sk_state) &
				       ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)), &wait);
		remove_wait_queue(sk_sleep(sk), &wait);
		sk->sk_write_pending--;
	} while (!done);
	return 0;
}