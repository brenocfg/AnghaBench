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
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sockaddr_atmsvc {scalar_t__ sas_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int sk_err; } ;
struct atm_vcc {int /*<<< orphan*/  flags; struct sockaddr_atmsvc local; } ;

/* Variables and functions */
 scalar_t__ AF_ATMSVC ; 
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_BOUND ; 
 int /*<<< orphan*/  ATM_VF_HASQOS ; 
 int /*<<< orphan*/  ATM_VF_REGIS ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAFNOSUPPORT ; 
 int EBADFD ; 
 int EINVAL ; 
 int EISCONN ; 
 int EUNATCH ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_UNCONNECTED ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  as_bind ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd ; 
 int /*<<< orphan*/  sigd_enq (struct atm_vcc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr_atmsvc*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int svc_bind(struct socket *sock, struct sockaddr *sockaddr,
		    int sockaddr_len)
{
	DEFINE_WAIT(wait);
	struct sock *sk = sock->sk;
	struct sockaddr_atmsvc *addr;
	struct atm_vcc *vcc;
	int error;

	if (sockaddr_len != sizeof(struct sockaddr_atmsvc))
		return -EINVAL;
	lock_sock(sk);
	if (sock->state == SS_CONNECTED) {
		error = -EISCONN;
		goto out;
	}
	if (sock->state != SS_UNCONNECTED) {
		error = -EINVAL;
		goto out;
	}
	vcc = ATM_SD(sock);
	addr = (struct sockaddr_atmsvc *) sockaddr;
	if (addr->sas_family != AF_ATMSVC) {
		error = -EAFNOSUPPORT;
		goto out;
	}
	clear_bit(ATM_VF_BOUND, &vcc->flags);
	    /* failing rebind will kill old binding */
	/* @@@ check memory (de)allocation on rebind */
	if (!test_bit(ATM_VF_HASQOS, &vcc->flags)) {
		error = -EBADFD;
		goto out;
	}
	vcc->local = *addr;
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq(vcc, as_bind, NULL, NULL, &vcc->local);
	for (;;) {
		prepare_to_wait(sk_sleep(sk), &wait, TASK_UNINTERRUPTIBLE);
		if (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			break;
		schedule();
	}
	finish_wait(sk_sleep(sk), &wait);
	clear_bit(ATM_VF_REGIS, &vcc->flags); /* doesn't count */
	if (!sigd) {
		error = -EUNATCH;
		goto out;
	}
	if (!sk->sk_err)
		set_bit(ATM_VF_BOUND, &vcc->flags);
	error = -sk->sk_err;
out:
	release_sock(sk);
	return error;
}