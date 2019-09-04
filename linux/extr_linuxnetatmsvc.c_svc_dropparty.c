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
struct sock {int /*<<< orphan*/  sk_err_soft; } ;
struct atm_vcc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  as_dropparty ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd ; 
 int /*<<< orphan*/  sigd_enq2 (struct atm_vcc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int svc_dropparty(struct socket *sock, int ep_ref)
{
	DEFINE_WAIT(wait);
	struct sock *sk = sock->sk;
	struct atm_vcc *vcc = ATM_SD(sock);
	int error;

	lock_sock(sk);
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq2(vcc, as_dropparty, NULL, NULL, NULL, NULL, ep_ref);
	for (;;) {
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
		if (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			break;
		schedule();
	}
	finish_wait(sk_sleep(sk), &wait);
	if (!sigd) {
		error = -EUNATCH;
		goto out;
	}
	error = -xchg(&sk->sk_err_soft, 0);
out:
	release_sock(sk);
	return error;
}