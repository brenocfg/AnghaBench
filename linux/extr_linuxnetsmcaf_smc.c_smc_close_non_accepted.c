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
struct socket {int dummy; } ;
struct sock {scalar_t__ sk_state; TYPE_1__* sk_prot; int /*<<< orphan*/  sk_shutdown; scalar_t__ sk_lingertime; } ;
struct smc_sock {int /*<<< orphan*/  conn; scalar_t__ use_fallback; struct socket* clcsock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 scalar_t__ SMC_CLOSED ; 
 scalar_t__ SMC_MAX_STREAM_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  smc_close_active (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_conn_free (int /*<<< orphan*/ *) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void smc_close_non_accepted(struct sock *sk)
{
	struct smc_sock *smc = smc_sk(sk);

	lock_sock(sk);
	if (!sk->sk_lingertime)
		/* wait for peer closing */
		sk->sk_lingertime = SMC_MAX_STREAM_WAIT_TIMEOUT;
	if (!smc->use_fallback) {
		smc_close_active(smc);
		sock_set_flag(sk, SOCK_DEAD);
		sk->sk_shutdown |= SHUTDOWN_MASK;
	}
	if (smc->clcsock) {
		struct socket *tcp;

		tcp = smc->clcsock;
		smc->clcsock = NULL;
		sock_release(tcp);
	}
	if (smc->use_fallback) {
		sock_put(sk); /* passive closing */
		sk->sk_state = SMC_CLOSED;
	} else {
		if (sk->sk_state == SMC_CLOSED)
			smc_conn_free(&smc->conn);
	}
	release_sock(sk);
	sk->sk_prot->unhash(sk);
	sock_put(sk); /* final sock_put */
}