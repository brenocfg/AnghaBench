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
struct TYPE_4__ {int /*<<< orphan*/  (* sk_write_space ) (TYPE_2__*) ;TYPE_1__* sk_socket; } ;
struct smc_sock {TYPE_2__ sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void smc_tx_sndbuf_nonfull(struct smc_sock *smc)
{
	if (smc->sk.sk_socket &&
	    test_bit(SOCK_NOSPACE, &smc->sk.sk_socket->flags))
		smc->sk.sk_write_space(&smc->sk);
}