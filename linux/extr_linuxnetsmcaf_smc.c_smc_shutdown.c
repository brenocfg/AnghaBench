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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_shutdown; } ;
struct smc_sock {TYPE_2__* clcsock; scalar_t__ use_fallback; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int sk_shutdown; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int SHUTDOWN_MASK ; 
#define  SHUT_RD 130 
#define  SHUT_RDWR 129 
#define  SHUT_WR 128 
 scalar_t__ SMC_ACTIVE ; 
 scalar_t__ SMC_APPCLOSEWAIT1 ; 
 scalar_t__ SMC_APPCLOSEWAIT2 ; 
 scalar_t__ SMC_APPFINCLOSEWAIT ; 
 scalar_t__ SMC_CLOSED ; 
 scalar_t__ SMC_PEERCLOSEWAIT1 ; 
 scalar_t__ SMC_PEERCLOSEWAIT2 ; 
 int kernel_sock_shutdown (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int smc_close_active (struct smc_sock*) ; 
 int smc_close_shutdown_write (struct smc_sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 

__attribute__((used)) static int smc_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = -EINVAL;
	int rc1 = 0;

	smc = smc_sk(sk);

	if ((how < SHUT_RD) || (how > SHUT_RDWR))
		return rc;

	lock_sock(sk);

	rc = -ENOTCONN;
	if ((sk->sk_state != SMC_ACTIVE) &&
	    (sk->sk_state != SMC_PEERCLOSEWAIT1) &&
	    (sk->sk_state != SMC_PEERCLOSEWAIT2) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT1) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT2) &&
	    (sk->sk_state != SMC_APPFINCLOSEWAIT))
		goto out;
	if (smc->use_fallback) {
		rc = kernel_sock_shutdown(smc->clcsock, how);
		sk->sk_shutdown = smc->clcsock->sk->sk_shutdown;
		if (sk->sk_shutdown == SHUTDOWN_MASK)
			sk->sk_state = SMC_CLOSED;
		goto out;
	}
	switch (how) {
	case SHUT_RDWR:		/* shutdown in both directions */
		rc = smc_close_active(smc);
		break;
	case SHUT_WR:
		rc = smc_close_shutdown_write(smc);
		break;
	case SHUT_RD:
		rc = 0;
		/* nothing more to do because peer is not involved */
		break;
	}
	if (smc->clcsock)
		rc1 = kernel_sock_shutdown(smc->clcsock, how);
	/* map sock_shutdown_cmd constants to sk_shutdown value range */
	sk->sk_shutdown |= how + 1;

out:
	release_sock(sk);
	return rc ? rc : rc1;
}