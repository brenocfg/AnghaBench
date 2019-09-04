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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_1__* sk_prot; int /*<<< orphan*/  sk_shutdown; } ;
struct smc_sock {int /*<<< orphan*/  conn; scalar_t__ use_fallback; int /*<<< orphan*/  clcsock_release_lock; int /*<<< orphan*/ * clcsock; int /*<<< orphan*/ * connect_info; int /*<<< orphan*/  connect_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ SMC_CLOSED ; 
 scalar_t__ SMC_INIT ; 
 scalar_t__ SMC_LISTEN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int kernel_sock_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int smc_close_active (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_conn_free (int /*<<< orphan*/ *) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static int smc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = 0;

	if (!sk)
		goto out;

	smc = smc_sk(sk);

	/* cleanup for a dangling non-blocking connect */
	flush_work(&smc->connect_work);
	kfree(smc->connect_info);
	smc->connect_info = NULL;

	if (sk->sk_state == SMC_LISTEN)
		/* smc_close_non_accepted() is called and acquires
		 * sock lock for child sockets again
		 */
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	else
		lock_sock(sk);

	if (!smc->use_fallback) {
		rc = smc_close_active(smc);
		sock_set_flag(sk, SOCK_DEAD);
		sk->sk_shutdown |= SHUTDOWN_MASK;
	}

	sk->sk_prot->unhash(sk);

	if (smc->clcsock) {
		if (smc->use_fallback && sk->sk_state == SMC_LISTEN) {
			/* wake up clcsock accept */
			rc = kernel_sock_shutdown(smc->clcsock, SHUT_RDWR);
		}
		mutex_lock(&smc->clcsock_release_lock);
		sock_release(smc->clcsock);
		smc->clcsock = NULL;
		mutex_unlock(&smc->clcsock_release_lock);
	}
	if (smc->use_fallback) {
		if (sk->sk_state != SMC_LISTEN && sk->sk_state != SMC_INIT)
			sock_put(sk); /* passive closing */
		sk->sk_state = SMC_CLOSED;
		sk->sk_state_change(sk);
	}

	/* detach socket */
	sock_orphan(sk);
	sock->sk = NULL;
	if (!smc->use_fallback && sk->sk_state == SMC_CLOSED)
		smc_conn_free(&smc->conn);
	release_sock(sk);

	sock_put(sk); /* final sock_put */
out:
	return rc;
}