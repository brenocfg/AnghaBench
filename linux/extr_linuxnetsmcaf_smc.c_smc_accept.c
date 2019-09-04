#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes_to_rcv; } ;
struct TYPE_4__ {scalar_t__ sk_state; } ;
struct smc_sock {int sockopt_defer_accept; TYPE_3__ conn; TYPE_2__* clcsock; scalar_t__ use_fallback; TYPE_1__ sk; } ;
struct TYPE_5__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int MSEC_PER_SEC ; 
 int O_NONBLOCK ; 
 scalar_t__ SMC_LISTEN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  sk_wait_data (struct sock*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 struct sock* smc_accept_dequeue (struct sock*,struct socket*) ; 
 int /*<<< orphan*/  smc_rx_data_available ; 
 int /*<<< orphan*/  smc_rx_wait (struct smc_sock*,long*,int /*<<< orphan*/ ) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int sock_error (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int smc_accept(struct socket *sock, struct socket *new_sock,
		      int flags, bool kern)
{
	struct sock *sk = sock->sk, *nsk;
	DECLARE_WAITQUEUE(wait, current);
	struct smc_sock *lsmc;
	long timeo;
	int rc = 0;

	lsmc = smc_sk(sk);
	sock_hold(sk); /* sock_put below */
	lock_sock(sk);

	if (lsmc->sk.sk_state != SMC_LISTEN) {
		rc = -EINVAL;
		release_sock(sk);
		goto out;
	}

	/* Wait for an incoming connection */
	timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);
	add_wait_queue_exclusive(sk_sleep(sk), &wait);
	while (!(nsk = smc_accept_dequeue(sk, new_sock))) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (!timeo) {
			rc = -EAGAIN;
			break;
		}
		release_sock(sk);
		timeo = schedule_timeout(timeo);
		/* wakeup by sk_data_ready in smc_listen_work() */
		sched_annotate_sleep();
		lock_sock(sk);
		if (signal_pending(current)) {
			rc = sock_intr_errno(timeo);
			break;
		}
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(sk_sleep(sk), &wait);

	if (!rc)
		rc = sock_error(nsk);
	release_sock(sk);
	if (rc)
		goto out;

	if (lsmc->sockopt_defer_accept && !(flags & O_NONBLOCK)) {
		/* wait till data arrives on the socket */
		timeo = msecs_to_jiffies(lsmc->sockopt_defer_accept *
								MSEC_PER_SEC);
		if (smc_sk(nsk)->use_fallback) {
			struct sock *clcsk = smc_sk(nsk)->clcsock->sk;

			lock_sock(clcsk);
			if (skb_queue_empty(&clcsk->sk_receive_queue))
				sk_wait_data(clcsk, &timeo, NULL);
			release_sock(clcsk);
		} else if (!atomic_read(&smc_sk(nsk)->conn.bytes_to_rcv)) {
			lock_sock(nsk);
			smc_rx_wait(smc_sk(nsk), &timeo, smc_rx_data_available);
			release_sock(nsk);
		}
	}

out:
	sock_put(sk); /* sock_hold above */
	return rc;
}