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
struct sock {int sk_shutdown; int sk_err; scalar_t__ sk_state; } ;
struct caifsock {struct sock sk; } ;

/* Variables and functions */
 scalar_t__ CAIF_CONNECTED ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ECONNRESET ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int SHUTDOWN_MASK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ sock_writeable (struct sock*) ; 
 scalar_t__ tx_flow_is_on (struct caifsock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static long caif_wait_for_flow_on(struct caifsock *cf_sk,
				  int wait_writeable, long timeo, int *err)
{
	struct sock *sk = &cf_sk->sk;
	DEFINE_WAIT(wait);
	for (;;) {
		*err = 0;
		if (tx_flow_is_on(cf_sk) &&
			(!wait_writeable || sock_writeable(&cf_sk->sk)))
			break;
		*err = -ETIMEDOUT;
		if (!timeo)
			break;
		*err = -ERESTARTSYS;
		if (signal_pending(current))
			break;
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
		*err = -ECONNRESET;
		if (sk->sk_shutdown & SHUTDOWN_MASK)
			break;
		*err = -sk->sk_err;
		if (sk->sk_err)
			break;
		*err = -EPIPE;
		if (cf_sk->sk.sk_state != CAIF_CONNECTED)
			break;
		timeo = schedule_timeout(timeo);
	}
	finish_wait(sk_sleep(sk), &wait);
	return timeo;
}