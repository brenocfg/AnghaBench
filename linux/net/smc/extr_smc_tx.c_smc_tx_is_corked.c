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
struct tcp_sock {int nonagle; } ;
struct smc_sock {TYPE_1__* clcsock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int TCP_NAGLE_CORK ; 
 struct tcp_sock* tcp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool smc_tx_is_corked(struct smc_sock *smc)
{
	struct tcp_sock *tp = tcp_sk(smc->clcsock->sk);

	return (tp->nonagle & TCP_NAGLE_CORK) ? true : false;
}