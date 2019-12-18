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
struct sock {scalar_t__ sk_state; int sk_max_ack_backlog; scalar_t__ sk_ack_backlog; } ;
struct smc_sock {int /*<<< orphan*/  tcp_listen_work; TYPE_2__* clcsock; int /*<<< orphan*/  use_fallback; scalar_t__ connect_nonblock; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int syn_smc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SMC_INIT ; 
 scalar_t__ SMC_LISTEN ; 
 int kernel_listen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 TYPE_1__* tcp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc;

	smc = smc_sk(sk);
	lock_sock(sk);

	rc = -EINVAL;
	if ((sk->sk_state != SMC_INIT && sk->sk_state != SMC_LISTEN) ||
	    smc->connect_nonblock)
		goto out;

	rc = 0;
	if (sk->sk_state == SMC_LISTEN) {
		sk->sk_max_ack_backlog = backlog;
		goto out;
	}
	/* some socket options are handled in core, so we could not apply
	 * them to the clc socket -- copy smc socket options to clc socket
	 */
	smc_copy_sock_settings_to_clc(smc);
	if (!smc->use_fallback)
		tcp_sk(smc->clcsock->sk)->syn_smc = 1;

	rc = kernel_listen(smc->clcsock, backlog);
	if (rc)
		goto out;
	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
	sk->sk_state = SMC_LISTEN;
	sock_hold(sk); /* sock_hold in tcp_listen_worker */
	if (!schedule_work(&smc->tcp_listen_work))
		sock_put(sk);

out:
	release_sock(sk);
	return rc;
}