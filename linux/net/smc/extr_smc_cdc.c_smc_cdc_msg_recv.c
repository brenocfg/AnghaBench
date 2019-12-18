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
struct smc_sock {int /*<<< orphan*/  sk; } ;
struct smc_cdc_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_unlock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_cdc_msg_recv_action (struct smc_sock*,struct smc_cdc_msg*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_cdc_msg_recv(struct smc_sock *smc, struct smc_cdc_msg *cdc)
{
	sock_hold(&smc->sk);
	bh_lock_sock(&smc->sk);
	smc_cdc_msg_recv_action(smc, cdc);
	bh_unlock_sock(&smc->sk);
	sock_put(&smc->sk); /* no free sk in softirq-context */
}