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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct smc_sock {struct sock sk; struct smc_sock* listen_smc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ SMC_LISTEN ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  smc_accept_enqueue (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  smc_close_non_accepted (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void smc_listen_out(struct smc_sock *new_smc)
{
	struct smc_sock *lsmc = new_smc->listen_smc;
	struct sock *newsmcsk = &new_smc->sk;

	if (lsmc->sk.sk_state == SMC_LISTEN) {
		lock_sock_nested(&lsmc->sk, SINGLE_DEPTH_NESTING);
		smc_accept_enqueue(&lsmc->sk, newsmcsk);
		release_sock(&lsmc->sk);
	} else { /* no longer listening */
		smc_close_non_accepted(newsmcsk);
	}

	/* Wake up accept */
	lsmc->sk.sk_data_ready(&lsmc->sk);
	sock_put(&lsmc->sk); /* sock_hold in smc_tcp_listen_work */
}