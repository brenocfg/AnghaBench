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
struct smc_sock {struct sock sk; } ;

/* Variables and functions */
 scalar_t__ SMC_ACTIVE ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  smc_listen_out (struct smc_sock*) ; 

__attribute__((used)) static void smc_listen_out_connected(struct smc_sock *new_smc)
{
	struct sock *newsmcsk = &new_smc->sk;

	sk_refcnt_debug_inc(newsmcsk);
	if (newsmcsk->sk_state == SMC_INIT)
		newsmcsk->sk_state = SMC_ACTIVE;

	smc_listen_out(new_smc);
}