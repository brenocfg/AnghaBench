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
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {int sk_state; } ;
struct smc_sock {int connect_nonblock; int /*<<< orphan*/  connect_work; int /*<<< orphan*/  sk; TYPE_2__* clcsock; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int syn_smc; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EALREADY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int O_NONBLOCK ; 
#define  SMC_ACTIVE 129 
#define  SMC_INIT 128 
 int __smc_connect (struct smc_sock*) ; 
 int kernel_connect (TYPE_2__*,struct sockaddr*,int,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 
 TYPE_1__* tcp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_connect(struct socket *sock, struct sockaddr *addr,
		       int alen, int flags)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = -EINVAL;

	smc = smc_sk(sk);

	/* separate smc parameter checking to be safe */
	if (alen < sizeof(addr->sa_family))
		goto out_err;
	if (addr->sa_family != AF_INET && addr->sa_family != AF_INET6)
		goto out_err;

	lock_sock(sk);
	switch (sk->sk_state) {
	default:
		goto out;
	case SMC_ACTIVE:
		rc = -EISCONN;
		goto out;
	case SMC_INIT:
		rc = 0;
		break;
	}

	smc_copy_sock_settings_to_clc(smc);
	tcp_sk(smc->clcsock->sk)->syn_smc = 1;
	if (smc->connect_nonblock) {
		rc = -EALREADY;
		goto out;
	}
	rc = kernel_connect(smc->clcsock, addr, alen, flags);
	if (rc && rc != -EINPROGRESS)
		goto out;

	sock_hold(&smc->sk); /* sock put in passive closing */
	if (flags & O_NONBLOCK) {
		if (schedule_work(&smc->connect_work))
			smc->connect_nonblock = 1;
		rc = -EINPROGRESS;
	} else {
		rc = __smc_connect(smc);
		if (rc < 0)
			goto out;
		else
			rc = 0; /* success cases including fallback */
	}

out:
	release_sock(sk);
out_err:
	return rc;
}