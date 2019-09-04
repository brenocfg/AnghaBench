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
struct socket {struct sock* sk; } ;
struct sock {int sk_max_ack_backlog; int sk_err; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int ATM_BACKLOG_DEFAULT ; 
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_LISTEN ; 
 int /*<<< orphan*/  ATM_VF_SESSION ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int EUNATCH ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  as_listen ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_vcc*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd ; 
 int /*<<< orphan*/  sigd_enq (struct atm_vcc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_insert_socket (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int svc_listen(struct socket *sock, int backlog)
{
	DEFINE_WAIT(wait);
	struct sock *sk = sock->sk;
	struct atm_vcc *vcc = ATM_SD(sock);
	int error;

	pr_debug("%p\n", vcc);
	lock_sock(sk);
	/* let server handle listen on unbound sockets */
	if (test_bit(ATM_VF_SESSION, &vcc->flags)) {
		error = -EINVAL;
		goto out;
	}
	if (test_bit(ATM_VF_LISTEN, &vcc->flags)) {
		error = -EADDRINUSE;
		goto out;
	}
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq(vcc, as_listen, NULL, NULL, &vcc->local);
	for (;;) {
		prepare_to_wait(sk_sleep(sk), &wait, TASK_UNINTERRUPTIBLE);
		if (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			break;
		schedule();
	}
	finish_wait(sk_sleep(sk), &wait);
	if (!sigd) {
		error = -EUNATCH;
		goto out;
	}
	set_bit(ATM_VF_LISTEN, &vcc->flags);
	vcc_insert_socket(sk);
	sk->sk_max_ack_backlog = backlog > 0 ? backlog : ATM_BACKLOG_DEFAULT;
	error = -sk->sk_err;
out:
	release_sock(sk);
	return error;
}