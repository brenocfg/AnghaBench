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
struct TYPE_2__ {int /*<<< orphan*/  (* sk_state_change ) (TYPE_1__*) ;} ;
struct smc_sock {TYPE_1__ sk; scalar_t__ wait_close_tx_prepared; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void smc_close_wake_tx_prepared(struct smc_sock *smc)
{
	if (smc->wait_close_tx_prepared)
		/* wake up socket closing */
		smc->sk.sk_state_change(&smc->sk);
}