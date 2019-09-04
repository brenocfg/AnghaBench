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
struct sock {scalar_t__ sk_state; } ;
struct smc_sock {int /*<<< orphan*/  conn; struct sock sk; } ;

/* Variables and functions */
 scalar_t__ SMC_CLOSED ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  smc_conn_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_listen_out (struct smc_sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void smc_listen_out_err(struct smc_sock *new_smc)
{
	struct sock *newsmcsk = &new_smc->sk;

	if (newsmcsk->sk_state == SMC_INIT)
		sock_put(&new_smc->sk); /* passive closing */
	newsmcsk->sk_state = SMC_CLOSED;
	smc_conn_free(&new_smc->conn);

	smc_listen_out(new_smc);
}